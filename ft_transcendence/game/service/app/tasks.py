# myapp/tasks.py
from celery import shared_task
import time
import game
from django.core.cache import cache
from django.conf import settings
import redis
from .models import Player, InGame, PlayerStats, PonGames
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync

def send_suspention_notif(layer, group, pid):
    async_to_sync(layer.group_send)(
        group,
        {
            "type": 'send_notification',
            "message": "message",
            "avatar": "",
            "is_read": "",
            "size_notf": "",
            "time": "",
            "id": pid,  
            "_type": "eng_game_view"
        }
    )

@shared_task
def delayed_task(param, count):
    # Simulating a delayed task (10 seconds)
    try:
        time.sleep(10)
        game_pk = param.get("game_name_pk")
        p1_pk = param.get("p1_pk")
        p2_pk = param.get("p2_pk")
        p1notif = param.get("p1notif")
        p2notif = param.get("p2notif") 

        # with open("celery.txt", 'w') as file:
        #     file.write(f'p1 = {p1_pk}, p2 =  {p2_pk}')
        redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
        rediscleanbool = False
        layer = get_channel_layer()
        ele = Player.objects.filter(pk=p1_pk)
        if ele.exists():
            p1 = ele.first()
            if p1.is_connected == True:
                send_suspention_notif(layer, p1notif, p1.player_id)
                redis_instance.setex(f"dont_save_history_{p1.player_id}", 5, "val")
            else:
                rediscleanbool = True
            p1.delete()

        ele = Player.objects.filter(pk=p2_pk)
        if ele.exists():
            p2 = ele.first()
            if p2.is_connected == True:
                send_suspention_notif(layer, p2notif, p2.player_id)
                redis_instance.setex(f"dont_save_history_{p2.player_id}", 5, "val")

            else:
                rediscleanbool = True

            p2.delete()

        if rediscleanbool:
            sufix = "to_not_invite"
            redis_instance.delete(f'{sufix}_{p1.player_id}')
            redis_instance.delete(f'{sufix}_{p2.player_id}')
        redis_instance.close()
    except Exception as e:
        pass
        # with open("celery.txt", 'w') as file:
            # file.write(f'expt : {e}')
        # print(f"e: {e}")