import json
from datetime import datetime
import django
django.setup()
from channels.generic.websocket import AsyncWebsocketConsumer
from channels.layers import get_channel_layer
import asyncio
import time
from asgiref.sync import sync_to_async
from .models import queue
import requests
import requests.cookies
from django.http import JsonResponse, HttpRequest,HttpResponseServerError,HttpResponseRedirect
from django.db import connection

import redis
from django.conf import settings

async def delete_from_queue(id):
    ele = queue.objects.filter(socket_id=id)
    if await sync_to_async(ele.exists)():
        r = await sync_to_async(ele.delete)()

class sockets(AsyncWebsocketConsumer):
    def __init__(self):
        super().__init__()
        self.group_name = "queue_group"
        self.login = None
        self.player_id = None
        self.isPut = False

    async def connect(self):
        await self.accept()

        
    async def disconnect(self, close_code):
        await delete_from_queue(self.channel_name)
        try:
            await self.channel_layer.group_discard(self.group_name, self.channel_name)
        except Exception as e:
            pass
            # print("exited befor creating groupe --")

    async def chat_message(self, event):
        message = event["message"]
        await self.send(message)

    async def receive(self, text_data):
        if (self.isPut == False):
            self.isPut = True
            try :
                data = json.loads(text_data)
                # print(data)
                self.group_name = f'in_queue_{self.login}'
                self.login = data.get('login')
                self.player_id = data.get('id')
                await self.channel_layer.group_add(
                        self.group_name, 
                        self.channel_name
                    )
                await self.placeinQueue()

            except Exception as e:
                # print(e)
                # print("faile ----------------")
                # await self.send('authantication required')
                await self.close()

        pass

    async def placeinQueue(self):
        ele = await sync_to_async(queue.objects.filter)(player_id=self.player_id)
        if await sync_to_async(ele.exists)():
            await self.canscel_signal("user already registerd for game")
            return
        
        redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
        sufix = "to_not_invite"
        val  = redis_instance.get(f'{sufix}_{self.player_id}')
        redis_instance.close()

        if val:
            await self.canscel_signal("user already playing a game")
            return

        var = queue(
                player_id = self.player_id,
                socket_id = self.channel_name,
                login     = self.login,
                groupe    = self.group_name
            )
        r = await sync_to_async(var.save)()

        queryset = queue.objects.order_by("joined_at")[:2]
        data = await sync_to_async(list)(queryset)
        # print(data)
        if len(data) == 2:
            await delete_from_queue(data[0].socket_id)
            await delete_from_queue(data[1].socket_id)
            # print("deleting both and creating  game")
            res = await self.create_game(data[0].player_id, data[1].player_id)
            if res == None:
                await self.canscel_signal2("game service can't create this match", data[0].groupe, data[1].groupe)
            else :
                await self.redirect_signal(data[0].groupe, data[1].groupe)
            

    async def create_game(self, p1, p2):

        url = 'http://game:8000/api/create/'
        data = {
            'player1' : p1,
            'player2' : p2,
        }
        # print("msg set to game is ")
        # print(data)
        # sends name
        try:
            
            res = await sync_to_async(requests.post)(url=url,json=data, timeout=5)
            if res.ok:
                return res
            else:
                return None
        except Exception as e:
            # print(f"exception {e}")
            return None    

    async def canscel_signal2(self, message, g1, g2):
        ch = get_channel_layer()
        await ch.group_send(g1, {
                'type': 'cancel_search', 
                "message": message
            })

        await ch.group_send(g2, {
                'type': 'cancel_search', 
                "message": message
            })

    async def canscel_signal(self, message):
        await self.send(json.dumps({
            'action' : "cancel_search",
            'message': message,
        }))

    async def redirect_signal(self, p1, p2):
        ch = get_channel_layer()
        json_data = {
            'action' : 'redirect',
        }
        await ch.group_send(p1, {
                'type': 'chat_message', 
                "message": json.dumps(json_data)
            })

        await ch.group_send(p2, {
                'type': 'chat_message', 
                "message": json.dumps(json_data)
            })