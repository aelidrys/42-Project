from asgiref.sync import sync_to_async

import django
django.setup()

from .models import Profile
from django.contrib.auth.models import User

from django.core.cache import cache
from django.conf import settings
import requests
import redis
import re
import json

from channels.generic.websocket import AsyncWebsocketConsumer
from channels.layers import get_channel_layer


async def get_profile(user):
    try:
        return await sync_to_async(Profile.objects.get)(user=user)
    except Profile.DoesNotExist:
        return None  
async def get_user_by_id(user_id):
    try:
        return await sync_to_async(User.objects.get)(pk=user_id)
    except User.DoesNotExist:
        return None  


def check_key_from_cache(redis_instence, key):
    keys = redis_instence.keys(key)  # Use '*' to match all keys
    existing_keys = [key.decode('utf-8') for key in keys]  # Decode bytes to strings
    if len(existing_keys) == 1:
        return True
    else:
        return False

def add_key_to_cache(redis_instence, key, value, time):
    redis_instence.setex(key, time, value)

async def game_invite(obj,data ,user_group_name , notiftype, avatar, message ,ruser, channel_layer):
    redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
    exist = check_key_from_cache(redis_instance, f'asgi:group:notification_user_{ruser.id}')
    if exist:
        #form key
        invit_key =  f'game_invite_{obj.user.id}_{ruser.id}'
        #invite already exist
        if check_key_from_cache(redis_instance, invit_key) == True:
            redis_instance.close()
            return
        
        sufix = "to_not_invite"
        if check_key_from_cache(redis_instance, f'{sufix}_{ruser.id}') == True:
            await player_is_ingame(obj, data['message'], channel_layer)
            return

        add_key_to_cache(redis_instance, invit_key , f"{obj.user.username}_{ruser.username}_{obj.channel_name}", 50)
        notiftype = data['type']
        avatar = data['avatar']
        message = data['message']
    else:
        user_group_name = obj.room_group_name
        message = f'{ruser.username} is offline'
        notiftype = 'error'

    redis_instance.close()
    await channel_layer.group_send(
        user_group_name,
        {
            "type": "send_notification",
            "message": message,
            "avatar": avatar,
            "is_read": "",
            "size_notf": "",
            "time": "",
            "id": obj.channel_name,  
            "_type": notiftype
        }
    )

def remove_all_associated_invites(name, redis_instance):
    keys = redis_instance.keys(f'*{name}*')
    regex = re.compile(
        rf"^game_invite_"
    )

    useres_to_notify = {}
    for key in keys:
        key = key.decode('utf-8')
        if regex.match(key) is not None:
            redis_instance.delete(key)
            parts = key.split('_')
            if parts[2] not in useres_to_notify:
                useres_to_notify[parts[2]] = []
            if parts[3] not in useres_to_notify:
                useres_to_notify[parts[3]] = []

            useres_to_notify[parts[2]].append(key)
            useres_to_notify[parts[3]].append(key)
        
    return useres_to_notify

async def send_update_for_previos_notification(obj, toupdate, channel_layer):
    for user,value in toupdate.items():
        ruserchanel = f'notification_user_{user}'
        await channel_layer.group_send(
            ruserchanel,
            {
                "type": "send_notification",
                "message": value,
                "avatar": "",
                "is_read": "",
                "size_notf": "",
                "time": "",
                "id": "",  
                "_type": "remove_invites",
            }
        )

async def create_game(obj, p1, p2):
    url = 'http://game:8000/api/create/'
    data = {
        'player1' : p1,
        'player2' : p2,
    }

    try:
        res = await sync_to_async(requests.post)(url=url, json=data, timeout=5)
        if res.ok:
            return res
        else:
            return None
    except Exception as e:
        return None

async def error_game_msg(obj, user,channel_layer, channel_name1 , channel_name2):
    ruserchanel = f'notification_user_{user}'
    await channel_layer.group_send(
        ruserchanel,
        {
            "type": "send_notification",
            "message": user,
            "avatar": "",
            "is_read": "",
            "size_notf": "",
            "time": "",
            "id": [channel_name1, channel_name2],  
            "_type": "error_game",
        }
    )


async def start_game_msg(obj, user,channel_layer, channel_name1 , channel_name2):
    ruserchanel = f'notification_user_{user}'
    await channel_layer.group_send(
        ruserchanel,
        {
            "type": "send_notification",
            "message": user,
            "avatar": "",
            "is_read": "",
            "size_notf": "",
            "time": "",
            "id": [channel_name1, channel_name2],  
            "_type": "start_playing",
        }
    )

async def player_is_ingame2(obj, data, channel_layer, ruserchanel):
    await channel_layer.group_send(
        ruserchanel,
        {
            "type": "send_notification",
            "message": f"one of these players is in a activity",
            "avatar": "",
            "is_read": "",
            "size_notf": "",
            "time": "",
            "id": "",  
            "_type": "player_is_ingame",
        }
    )

async def player_is_ingame(obj, data, channel_layer):
    ruserchanel = f'notification_user_{data["sender"]["id"]}'
    await channel_layer.group_send(
        ruserchanel,
        {
            "type": "send_notification",
            "message": f"{data['recever']['username']} is in game",
            "avatar": "",
            "is_read": "",
            "size_notf": "",
            "time": "",
            "id": "",  
            "_type": "player_is_ingame",
        }
    )


async def game_accept(obj, data, channel_layer):
    receiver = data['recever']
    sender = data['sender']

    parts = data['invite_key'].split('_')

    if len(parts) == 4:
        if obj.user.id != int(parts[3]):
            return
    else:
        return
    
    redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
    val = redis_instance.get(data['invite_key'])
    if val is None:
        return

    

    if data['channel_name'] != obj.channel_name:
        return    
    
    gamename = val.decode('utf-8')
    names = gamename.split('_')

    notifs = remove_all_associated_invites(parts[3], redis_instance)
    notifs2 = remove_all_associated_invites(parts[2], redis_instance)
    notifs.update(notifs2)
    
    sufix = "to_not_invite"
    booll1 = check_key_from_cache(redis_instance, f'{sufix}_{parts[2]}')
    booll2 = check_key_from_cache(redis_instance, f'{sufix}_{parts[3]}')
    redis_instance.close()

    if booll1 == True or booll2 == True:
        layer1 = f'notification_user_{parts[2]}'
        layer2 = f'notification_user_{parts[3]}'
        await player_is_ingame2(obj, data['message'], channel_layer,layer1)
        await player_is_ingame2(obj, data['message'], channel_layer, layer2)
        return
    
    await send_update_for_previos_notification(obj, notifs, channel_layer)
    res = await create_game(obj, parts[2], parts[3])

    if res == None:
        await error_game_msg(obj, parts[2], channel_layer, obj.channel_name, names[2])
        await error_game_msg(obj, parts[3], channel_layer, obj.channel_name, names[2])
    else:
        await start_game_msg(obj, parts[2], channel_layer, obj.channel_name, names[2])
        await start_game_msg(obj, parts[3], channel_layer, obj.channel_name, names[2])
    

async def game_decline(obj, data, channel_layer):
    parts = data['invite_key'].split('_')
    if len(parts) == 4:
        if (obj.user.id != int(parts[3])):
            return
    else:
        return
    redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
    if check_key_from_cache(redis_instance, data['invite_key']) == False:
        return
    deleted_count = redis_instance.delete(data['invite_key'])
    ruserchanel = ""
    notiftype = "invite_decline"
    if deleted_count == 0:
        return
    else:
        ruserchanel = f"notification_user_{parts[2]}"
        redis_instance.close()
        message = f"{obj.user.username} has declined"
        notiftype = "invite_decline"

    await channel_layer.group_send(
        ruserchanel,
        {
            "type": "send_notification",
            "message": message,
            "avatar": "",
            "is_read": "",
            "size_notf": "",
            "time": "",
            "id": "",  
            "_type": notiftype
        }
    )

    async def eng_game_view(obj):
        await obj.send(text_data=json.dumps({
            'id': id,
            'message': "eng_game_view",
            'avatar': avatar,
            'is_read': is_read,
            'size_notf': size,
            'time': time,
            '_type': "eng_game_view"
        }))
    
class NotificationConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        self.user = self.scope['user']
        if self.user.is_anonymous:
            await self.close()
        else:
            self.room_name = f'user_{self.user.id}'
            self.room_group_name = f'notification_{self.room_name}'
            await self.setStatus(True)
            await self.channel_layer.group_add(
                self.room_group_name,
                self.channel_name
            )
            await self.accept()
            
    
    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(
            self.room_group_name,
            self.channel_name
        )
        if self.user.is_anonymous:
            return
        await self.setStatus(False)

    async def receive(self, text_data):
        data = json.loads(text_data)

        id = data["user_id"]
        if self.user.is_anonymous:
            return

        message = ""
        avatar = ""
        is_read = ""
        size_notf = ""
        notiftype = "update"
        
        ruser =  await get_user_by_id(id)#id ta3 resiver
        if ruser is None:
            return

        channel_layer = get_channel_layer()
        room_name = f'user_{ruser.id}'
        user_group_name = f"notification_{room_name}" #reciver groupname

        if data['type'] == "eng_game_view":
            eng_game_view(self)
            return

        if data['type'] == 'invite_game':
            await game_invite(
                self, data,
                user_group_name,
                notiftype, avatar,
                message, ruser,
                channel_layer
            )
            return
        
        elif data['type'] == 'inivte_cancel':
            await game_decline(self, data, channel_layer)
            return
        
        elif data['type'] == 'inivte_accept':
            await game_accept(self , data, channel_layer)
            return
        elif data['type'] == 'player_is_ingame':
            await player_is_ingame(self , data, channel_layer)
            return
        
        await channel_layer.group_send(
            user_group_name,
            {
                "type": "send_notification",
                "message": message,
                "avatar": avatar,
                "is_read": is_read,
                "size_notf": size_notf,
                "time": "",
                  "id": "",  
                "_type": notiftype
            }
        )
    
    async def send_notification(self, event):

        message = event['message']
        avatar = event['avatar']
        is_read = event['is_read']
        size = event['size_notf']
        _type = event['_type']
        id = event['id']  
        time = event['time']
        
        if _type == 'invite_game':
            id = self.channel_name

        if _type == 'start_playing':
            if self.channel_name not in id:
                return

        await self.send(text_data=json.dumps({
            'id': id,
            'message': message,
            'avatar': avatar,
            'is_read': is_read,
            'size_notf': size,
            'time': time,
            '_type': _type
        }))

        
    async def setStatus(self,case):
        profile = await get_profile(self.user)
        profile.is_online = case
        await sync_to_async(profile.save)()

