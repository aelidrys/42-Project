from channels.generic.websocket import WebsocketConsumer
from channels.generic.websocket import AsyncWebsocketConsumer
from asgiref.sync import async_to_sync, sync_to_async
import json
import django
import asyncio
from channels.layers import get_channel_layer

from django.core.cache import cache
from django.conf import settings
import redis
# local import
django.setup()
from .models import Tournament
from .tournament import is_user_subscribe, player_disconnect

class WSConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.user_id = self.scope.get("user")['user_id']
        try:
            trn = await sync_to_async(Tournament.objects.latest)("id")
        except Exception as e:
            # print('connection Faild!!!!!! \n EXCEPTION:     ', e, flush=True)
            return
        self.room_group_name = f'trnGroup_{trn.pk}'
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name,
        )
        await self.accept()
        
        redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
        prefix = "inTourn"
        redis_instance.set(f'{prefix}_{self.user_id}', "dont invite")
        redis_instance.close()
        # print(f'user with id {self.user_id} CONNCTED', flush=True)

    async def receive(self, text_data):
        pass
        # print(text_data)
        # print('consumer receive', flush=True)


    async def disconnect(self, close_code):
        # print("DISCONNECT", flush=True)
        await self.channel_layer.group_discard(
            self.room_group_name,
            self.channel_name,
        )
        user_id = self.user_id
        redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
        prefix = "inTourn"
        redis_instance.delete(f'{prefix}_{user_id}')
        # print(f'user_id: {user_id} -> group_discard', flush=True)
        value = redis_instance.get(f'ontask_{user_id}')
        if value:
            # print(f'user_id: {user_id} -> already ON TASK', flush=True)
            await asyncio.sleep(5)
            redis_instance.delete(f'ontask_{user_id}')
        if value is None:
            # print(f'user_id: {user_id} -> start TASK', flush=True)
            redis_instance.set(f'ontask_{user_id}', 'isconnect')
            await asyncio.sleep(5)
            redis_instance.delete(f'ontask_{user_id}')
            try:
                player_id = await sync_to_async(is_user_subscribe)(user_id)
                # print("player: ==> ", player_id, flush=True)
                if player_id:
                    value = redis_instance.get(f'{prefix}_{user_id}')
                    if value:
                        pass
                        # print(f'USER with id {user_id} STILE CONNECT', flush=True)
                    else:
                        await sync_to_async(player_disconnect)(player_id, user_id)
                        # print(f'USER with id {user_id} DICONNECT', flush=True)
            except Exception as e:
                # print(f"Exception: ====> e: {e}", flush=True)
                pass
        redis_instance.close()
        # print(f'inTourn COLSED by user_id {user_id}', flush=True)



    async def update_tournament(self, event):
        # print('send_tournament_update called!!!', flush=True)
        players = event['tourn_players']
        unknown = event['unknown']
        trn_name = event['trn_name']
        trn_id = event['trn_id']
        await self.send(text_data=json.dumps({
            'type': 'tourn',
            'players': players,
            'unknown': unknown,
            'trn_name': trn_name,
            'trn_id': trn_id,
        }))


    async def start_matche(self, event):
        response = event['response']
        await self.send(text_data=json.dumps(response))
    
    async def matche_end(self, event):
        user_id = event['user_id']
        matche_res = event['matche_res']
        await self.send(text_data=json.dumps({
            'type': 'matche_end', 
            'user_id': user_id,
            'matche_res': matche_res,
        }))
        
        


        

class WSConsumer_trnInfo(WebsocketConsumer):
    def connect(self):
        self.room_group_name = 'tournament_info'

        async_to_sync(self.channel_layer.group_add)(
            self.room_group_name,
            self.channel_name,
        )
        self.accept()

    def disconnect(self, close_code):
        async_to_sync(self.channel_layer.group_discard)(
            self.room_group_name,
            self.channel_name,
        )


    def tourn_info(self, event):
        created = event['created']
        if created == True:
            self.send(text_data=json.dumps({
                'players': event['players'],
                'unknown': event['unknown'],
                'trn_name': event['trn_name'],
                'trn_id': event['trn_id'],
            }))
        if created == False:
            self.send(text_data=json.dumps({
                'players': [],
                'unknown': 0,
                'trn_name': '',
                'trn_id': event['trn_id'],
            }))



