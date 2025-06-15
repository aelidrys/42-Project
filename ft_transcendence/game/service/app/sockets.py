import json
import requests
import asyncio
import time
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.layers import get_channel_layer
from asgiref.sync import sync_to_async
import django
import redis
from django.conf import settings


django.setup()

from .models import InGame, Player, PlayerStats, PonGames
from django.db.models import Q

class sockets(AsyncWebsocketConsumer):
    def __init__(self):
        super().__init__()
        self.group_name = None
        self.player = None
        self.game =None
        self.gameend = False
        self.isdeleated = True
        self.started = False
        # self.sender_started = False

    async def connect(self):
        await self.accept()

    async def disconnect(self, close_code):
        if not self.game:
            return
        
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )

        if self.game.gametype == "normal":
            redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
            sufix = "to_not_invite"
            redis_instance.delete(f'{sufix}_{self.player.player_id}')
            redis_instance.close()

        if self.gameend == True:
            return

        try:
            winningside = 1 if self.player.side == 2 else 2
            await self.channel_layer.group_send(
                        self.group_name,
                        {
                            'type': 'chat_message',
                            'message': {
                                    'subject': 'surrender',
                                    'winer'  : winningside,
                                }
                            ,
                            'sender' : self.channel_name,
                        }
                    )

            if winningside == 1:
                winer = self.game.player1.player_id
            else:
                winer = self.game.player2.player_id
            
            p1score, p2score = (0, 0)
            if winningside == 1:
                p1score,p2score = (5, 0)
            else:
                p1score,p2score = (0, 5)
                
            await self.setHistoric({
                'winer' : winer,
                "p1score" : p1score,
                "p2score" : p2score,
                "order"   : "surrender"
            })

        except Exception as e:
            # print(f"exception : {e}")
            return


    async def receive(self, text_data):
        try :
            data = json.loads(text_data)
            response_msg = ""
            
            if self.game:
                if 'subject' not in data.keys():
                    return
                if data['subject'] == 'ready' and self.player.side == 2:
                    redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
                    val = redis_instance.get(f"sender_for_game_{self.game.pk}_is_ready")
                    
                    if val is None:
                        response_msg = {
                            'subject' : 'senderNotReady',
                        }
                    else:
                        response_msg = {
                            'subject' : 'startgame',
                        }
                        redis_instance.delete(f"sender_for_game_{self.game.pk}_is_ready", "im ready")
                    redis_instance.close()

                elif data['subject'] == 'ready' and self.player.side == 1:
                    redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
                    redis_instance.setex(f"sender_for_game_{self.game.pk}_is_ready",12 , "im ready")
                    redis_instance.close()
                    return
                elif data['subject'] == 'update':
                    response_msg = data
                elif data['subject'] == 'end':
                    response_msg = data
                    await self.setHistoric(data)

                
                await self.channel_layer.group_send(
                        self.group_name,
                        {
                            'type': 'chat_message',
                            'message': response_msg,
                            'sender' : self.channel_name,
                        }
                    )

            else:
                await self.find_game(data.get('id'))
        except Exception as e:
            # print(f"{e} -{json.loads(text_data).get('id')}-")
            if self.game:
                pass
            else:
                await self.send(text_data=json.dumps({
                    'subject' : 'eng_game_view',
                }))
                await self.close()

    async def chat_message(self, event):
        # Send message to WebSocket
        try :
            if self.gameend == True:
                return
            message = event['message']
            sender = event['sender']
            
            if message['subject'] == "end":
                self.gameend = True
            
            elif message['subject'] == "surrender":
                self.gameend = True

            elif message['subject'] == "senderNotReady":
                if sender == self.channel_name:
                    pass
                else:
                    return
            
            elif sender == self.channel_name:
                return
            

            await self.send(text_data=json.dumps(message))
        except Exception as e:
            pass
    

    async def find_game(self, myid):
        # raise ValueError('intentinal crash ana li drtha')
        select_querry = await sync_to_async(InGame.objects.select_related('player1', 'player2').filter)(
                Q(player1__player_id = myid) | Q(player2__player_id = myid)
            )
        if await sync_to_async(select_querry.exists)():  
            self.game = await sync_to_async(select_querry.first)() 
            self.player = await sync_to_async(Player.objects.get)(player_id=myid)
        else:
            raise ValueError(f"{myid} is not registerd in a game")
        
        # add connect this channel with game obj      
        self.group_name = self.game.groupName
        await self.channel_layer.group_add(self.group_name, self.channel_name)
        
        # udate database
        self.player.is_connected = True
        self.player.channel_id = self.channel_name
        await sync_to_async(self.player.save)()

        self.game = await sync_to_async(InGame.objects.select_related('player1', 'player2').get)(pk=self.game.id)
        p1 = self.game.player1
        p2 = self.game.player2

        if p1.is_connected == True and p2.is_connected == True:
            await sync_to_async(p1.delete)()
            await sync_to_async(p2.delete)()

        # send first message
        msg = {
            'subject': 'init',
            'p1name' : p1.login, 
            'p1img'  : p1.imageURL,
            'p2name' : p2.login,   
            'p2img'  : p2.imageURL,
            'side' : self.player.side,
            'type' : 'sender' if self.player.side == 1 else 'listner',
        }
        await self.send(json.dumps(msg))

    async def setHistoric(self, msg):
        redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
        val = redis_instance.get(f"dont_save_history_{self.player.player_id}")
        # print(val)
        # print(f"dont_save_history_{self.player.player_id}")
        if val is not None:
            redis_instance.delete(f"dont_save_history_{self.player.player_id}")
            redis_instance.close()
            return
        redis_instance.close()

        if self.game.gametype == 'tourn':
            return
        p1id = self.game.player1.player_id
        p2id = self.game.player2.player_id
        
        p1w = 1 if msg['p1score'] == 5 else 0
        p2w = 1 if msg['p2score'] == 5 else 0
        order = msg['order']
        try:
            p1stats = await sync_to_async(PlayerStats.objects.get)(player_id=p1id)
        except Exception as e:
            p1stats = PlayerStats()
            p1stats.player_id = p1id
        try:
            p2stats = await sync_to_async(PlayerStats.objects.get)(player_id=p2id)
        except Exception as e:
            p2stats = PlayerStats()
            p2stats.player_id = p2id
        
        p1stats.games_played += 1
        p1stats.wins += p1w
        p1stats.loss += p2w
        p1stats.goals_scored   += msg['p1score']
        p1stats.goals_conceded += msg['p2score']

        p2stats.games_played += 1
        p2stats.wins += p2w
        p2stats.loss += p1w
        p2stats.goals_scored   += msg['p2score']
        p2stats.goals_conceded += msg['p1score']
 
        glogs = PonGames()
        glogs.gamename = f"({p1id}) ({p2id})"
        glogs.player1 = p1id        
        glogs.player2 = p2id
        glogs.goals_order = order
        glogs.p1goal = msg['p1score']
        glogs.p2goal = msg['p2score']
        glogs.winner = msg['winer']
        glogs.created_at = self.game.created_at

        await sync_to_async(p1stats.save)()
        await sync_to_async(p2stats.save)()
        await sync_to_async(glogs.save)()

    # async def suspend_game():
    #     el1 = await sync_to_async(Player.objects.filter)(player_id=slef.game.player1.pk)
    #     ele2 = await sync_to_async(Player.objects.filter)(player_id=slef.game.player2.pk)

    #     if await sync_to_async(ele.exists)():
    #         p1 = await sync_to_async(ele.first)() 
    #         await sync_to_async(p1.delete)()
    #     if await sync_to_async(ele.exists)():
    #         p2 = await sync_to_async(ele.first)() 
    #         await sync_to_async(p2.delete)()
    #                 redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
    #     sufix = "to_not_invite"
    #     redis_instance.delete(f'{sufix}_{self.game.player1.player_id}')
    #     redis_instance.delete(f'{sufix}_{self.game.player1.player_id
    #     }')
    #     redis_instance.close()
