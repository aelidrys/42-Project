from django.views.decorators.csrf import csrf_exempt
from django.http import HttpResponse
from rest_framework.permissions import IsAuthenticated, AllowAny
from rest_framework.views import APIView
from .my_custom_auth import CustomJWTAuthentication
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from asgiref.sync import sync_to_async
from .models import Player, InGame, PlayerStats, PonGames
from django.core.serializers import serialize

from channels.layers import get_channel_layer
from django.core.cache import cache
from django.conf import settings
import redis

import requests
import json
import logging
from .tasks import delayed_task



#delet
def test(request):
    var1 = InGame.objects.all()
    var2 = Player.objects.all()
    msg = {
            "stat": "working..",
            "ingames_db": serialize('json', var1),
            "players": serialize('json', var2),
        }
    
    var3 = PlayerStats.objects.all()
    var4 = PonGames.objects.all()
    msg['stats'] = serialize('json', var3)
    msg['PonGames'] = serialize('json', var4)
    
    # var1.delete()
    var2.delete()
    var3.delete()
    var4.delete()
    return HttpResponse(json.dumps(msg), content_type='application/json')

# Create your views here.
def create_players(player, side):
    try:
        url = "http://django:8000/api/getUser/"
        headers = {'Content-Type': 'application/json'}  # Adjust headers as needed
        body = {"id"      : player}
        response = requests.post(url, json.dumps(body), headers=headers)

        # loggers.info(f'request sent to user service for information about user : {player}')
        if response.status_code != 200:
            raise ValueError(f"responce error {response.status_code}")
        val = json.loads(response.content)


        obj = Player(player_id = val.get('id') ,
            login=val.get('login'),
            side=side,channel_id=None,
            imageURL=val.get('image')
        )

        # loggers.info(f"player {player} created in table game.Players")
        return obj
    except Exception as e:
        # loggers.erorr(e)
        # print(f'player create exption : {e}')
        return None

@csrf_exempt
def creat_game(requst):
    try :
        body = json.loads(requst.body)

        #check if its the same player
        if body['player1'] == body['player2']:
            raise ValueError("not allowed")

        #check if a player is allready in a game
        a1 = Player.objects.filter(login=body['player1']).exists()
        a2 = Player.objects.filter(login=body['player2']).exists()


        if a1 or a2:
            raise ValueError("a player is allready in game")
      
        #create players
        p1 = create_players(body['player1'], 1)
        p2 = create_players(body['player2'], 2)

        gid = -1
        turnid = -1
        gametype = ""
        if "gametype" in body:
            gametype = body.get("gametype")
        else:
            gametype = "normal"
            
        if gid in body.values() and turnid in body.values():
            gid = body['gid']
            turnid = body['turnid']
            gametype = body["type"]
        
        #create gamme
        groupName = f""

        obj = InGame(
            player1 = p1,
            player2 = p2,
            game_started = False,
            gametype = gametype,
            gid = gid,
            turnid = turnid,
            groupName = f"group.name.{p1.player_id}.vs.{p2.player_id}",
        )
        p1.save()
        p2.save()    
        obj.save()
        if gametype == "normal":
            redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
            sufix = "to_not_invite"
            redis_instance.set(f'{sufix}_{p1.player_id}', "is in game")
            redis_instance.set(f'{sufix}_{p2.player_id}', "is in game")
            redis_instance.close()

        delayed_task.delay(
            {
                "game_name_pk" : obj.pk,
                "p1_pk" : p1.pk,  
                "p2_pk" : p2.pk,
                "p1notif" : f"notification_user_{p1.player_id}",
                "p2notif" : f"notification_user_{p2.player_id}",
            }, 10)
        return HttpResponse("game created")

    except Exception as e:
        # print(f'excepton error {e}')
        return HttpResponse(f"not games created reason : ${e}")
    
class is_in_game(APIView):
    pass


@api_view(['POST', 'GET'])
# @csrf_exempt
@authentication_classes([CustomJWTAuthentication])
def getstats(request):
    body = json.loads(request.body)
    id = body['id']
    login = body['name']
    gamecount = body['historycount']
    stats = None

    try:
        stats = PlayerStats.objects.get(player_id=id)
    except Exception as e:
        # print(e)
        stats = PlayerStats(player_id = id)

    key = f"({id})"
    games = []

    try:
        games = PonGames.objects.filter(gamename__icontains=key).order_by('-id')
    except Exception as e:
        games = []
        # print(f"exception {e}")

    stat_json = {
        'id' : stats.player_id,
        'login' : login,    
        'games_played' : stats.games_played,
        'wins' : stats.wins,
        'loss' : stats.loss,
        'goals_scored' : stats.goals_scored,
        'goals_conceded' : stats.goals_conceded,
    }

    gamelist = []
    for game in games:
        gamelist.append({
            'gamename'      : game.gamename,
            'player1'       : game.player1,
            'player2'       : game.player2,
            'created_at'    : game.created_at.strftime('%Y-%m-%d %H:%M:%S'),
            'goals_order'   : game.goals_order,
            'winner'        : game.winner,
            'p1goal'        : game.p1goal,
            'p2goal'        : game.p2goal
        })
    try :
        responce = {
            "user":  json.dumps(stat_json),
            "historic" : json.dumps(gamelist),
        }
    except Exception as e:
        pass
        # print(f"erorr : {e}")
    return HttpResponse(json.dumps(responce), content_type='application/json')


def send_to_sock(layer, group, message):
    layer.group_send(
        group,
        {
            "type": message,
            "message": "",
            "avatar": "",
            "is_read": "",
            "size_notf": "",
            "time": "",
            "id": "",  
            "_type": "message"
        }
    )

def delete_game(request):      
    body = json.loads(request.body)
    player_id = body.get("player_id")
    select_querry =  InGame.objects.select_related('player1', 'player2').filter(
        Q(player1__player_id = player_id) | Q(player2__player_id = player_id)
    )
    if select_querry.exists():  
        game = select_querry.first() 
        p1 = game.player1
        p2 = game.player2
        p1.delete()
        p2.delete()
        
        groupp1 = f'notification_user_{p1.player_id}'
        groupp2 = f'notification_user_{p2.player_id}'
        layer = get_channel_layer()
        send_to_sock(layer, groupp1, "eng_game_view")
        send_to_sock(layer, groupp2, "eng_game_view")
    return HttpResponse("done.")

@csrf_exempt
def remove_game(request):
    try:
        body = json.loads(request.body)
        id1 = body.get('id1')
        id2 = body.get('id2')
        try:
            p1 = Player.objects.get(player_id=id1)
            p1.delete()
        except:
            pass
        
        try:
            p2 = Player.objects.get(player_id=id2)
            p2.delete()
        except Exception as e:
            pass
            # print(f'delete inGame_player EXCEPTION: {e}')
        return HttpResponse("deleted")
    except Exception as e:
        # print(f'EXCEPTION: {e}')
        return HttpResponse("no delete")
    