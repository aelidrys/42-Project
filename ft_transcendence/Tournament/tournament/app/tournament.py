from .models import Tournament ,Player
from .matches import create_matches, send_match_start, player_left

from .enums import Tourn_status, Round
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync

from django.conf import settings
import redis

def tourn_subscribing(data):
    subs, tourn = get_or_create_tourn(data)
    if subs:
        t_players = tourn.trn_players.count()
        if t_players == 4:
            return tourn
    else:
        plyr = get_or_create_player(data, tourn)
        
        # saving in redis
        user_id = data['user']['id']
        redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
        sufix = "to_not_invite"
        redis_instance.set(f'{sufix}_{user_id}', "dont invite")
        redis_instance.close()
        
        # counting players        
        players = tourn.trn_players.all()
        players_nmb = players.count()
        if players_nmb == 4:
            send_tourn_info()
            tourn.status = Tourn_status.ST.value
            tourn.save()
            create_matches(tourn)
            send_match_start(tourn)
            for plyer in players:
                tourn_warn(plyer)
            return tourn
        else:
            send_tournament_update(tourn)
    return tourn


def tourn_warn(plyer: Player):
    user_id = plyer.profile_id
    channel_layer = get_channel_layer()
    room_name = f'chat_{user_id}'
    async_to_sync(channel_layer.group_send)(
        room_name,
        {
            'type': 'new_msg',
            'msg_id': -1,
            'sender_id': -1,
            'receiver_id': -1,
            'msg_text': 'tourn_warn',
            'unread_msgs': 0,
            'all_unread_msgs': 0,
            '_type': 'warn',
        }
    )



def get_or_create_player(data, trn):
    user_id = data['user']['id']
    user_name = data['user']['username']
    trn_name = data['tournament_name']
    # print('$$$$$$$$$$$ username: ', user_name, flush=True)
    plyr, created = Player.objects.get_or_create(profile_id=user_id, tournament=trn)
    if created:
        plyr.img_url = data['avatar']
        plyr.name = trn_name
        plyr.username = user_name
        plyr.save()
    else:
        plyr.img_url = data['avatar']
        plyr.name = trn_name
        plyr.username = user_name
        plyr.save()
    return plyr

def get_or_create_tourn(data):
    user_id = data['user']['id']
    t_count = Tournament.objects.count()
    # ----- no tourn exist ------- # 
    if t_count == 0:
        trn = Tournament.objects.create(size=4)
        trn.name = f'tourn_{trn.pk}'
        trn.round = Round.HF.value
        trn.save()
        return False, trn
    
    tourn = Tournament.objects.latest("id")
    plyr = is_user_subscribe(user_id)
    if plyr:
        return True, tourn
    if tourn.status != Tourn_status.PN.value:
        new_tourn = Tournament.objects.create(size=4)
        new_tourn.name = f'tourn_{new_tourn.pk}'
        new_tourn.save()
        return False, new_tourn
    return False, tourn



def is_user_subscribe(user_id) -> Player:
    try:
        tourn = Tournament.objects.latest("id")
        plyr = Player.objects.get(tournament=tourn, profile_id=user_id)
        if tourn.status != Tourn_status.EN.value and plyr.won:
            players_nmb = tourn.trn_players.all().filter(won=True).count()
            if players_nmb == 1 and tourn.status == Tourn_status.ST.value:
                # print('one player won', flush=True)
                tourn.status = Tourn_status.EN.value
                tourn.save()
            # print(f'player  {user_id} is subscribe', flush=True)
            return plyr.pk
    except Exception as e:
        # print('EXCEPTON: ===== ', e, flush=True)
        pass
    return None


def send_tournament_update(tourn: Tournament):
    channel_layer = get_channel_layer()
    room_group_name = f'trnGroup_{tourn.pk}'
    players = tourn.trn_players.all()

    async_to_sync(channel_layer.group_send)(
        room_group_name,
        {
            'type': 'update_tournament',
            'start_status': tourn.status,
            'tourn_players': [
                {'image_url': player.img_url, 'name': player.name}
                for player in players
            ],
            'unknown': tourn.size - tourn.trn_players.count(),
            'trn_name': tourn.name,
            'trn_id': tourn.id,
        }
    )
    # print('tourn_up send to group: {}'.format(room_group_name),
        # flush=True)




def generate_tourn_response(trn: Tournament):
    data = trn.trn_players.all()
    playerslist = []
    for player in data:
        playerslist.append({
            'image_url': player.img_url,
            'name': player.name,
        })
    
    resp_data = {
        'type': 'remotTrn',
        'created': True,
        'players': playerslist,
        'unknown': trn.size - len(playerslist),
        'trn_name': trn.name,
        'trn_id': trn.id,
        'create_time': trn.create_date.isoformat(),
    }
    return resp_data


def send_tourn_info():
    channel_layer = get_channel_layer()
    room_group_name = 'tournament_info'
    try:
        trn = Tournament.objects.latest('id')
        if trn.status == Tourn_status.PN.value:
            players = generate_tourn_response(trn)
            players['type'] = 'tourn_info'
            async_to_sync(channel_layer.group_send)(
                room_group_name,
                players,
            )
            return
    except:
        pass
    async_to_sync(channel_layer.group_send)(
        room_group_name,
        {
            'type': 'tourn_info', 
            'created': 'false',
            'trn_size': 4,
        },
    )   



def _leave_trn(user_id):
        try:
            trn = Tournament.objects.latest('id')
            plyr = Player.objects.get(profile_id=user_id, tournament=trn)
            plyr.delete()
            redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
            sufix = "to_not_invite"
            redis_instance.delete(f'{sufix}_{user_id}')
            # print(f'user {plyr.username} _leave_trn', flush=True)
            redis_instance.close()

        except:
            return {'status':'ko'}
        send_tourn_info()
        send_tournament_update(trn)
        # print(f'player id: {user_id} leave trn', flush=True)
        return {'status':'ok'}
  
def player_disconnect(p_id, user_id):
    player = Player.objects.get(id=p_id)
    try:
        if player.tournament.status == Tourn_status.PN.value:
            _leave_trn(user_id)
        if player.tournament.status == Tourn_status.ST.value:
            player_left(player)
    except Exception as e:
        pass
        # print(f'EXCEPTION at _leave_trn ===> Exc: {e}', flush=True)   

