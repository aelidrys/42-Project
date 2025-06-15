from channels.layers import get_channel_layer
from .models import Tournament, Matche, Player
from .enums import Round, M_status, Tourn_status
from django.shortcuts import render
from asgiref.sync import async_to_sync
import requests
from django.db.models import Q
import json
from django.db import transaction

from django.core.cache import cache
from django.conf import settings
import redis


def get_player(name):
    url = "http://django:8000/api/getUserByname/"
    headers = {'Content-Type': 'application/json'}  # Adjust headers as needed
    body = {"login"      : name}
    response = requests.post(url, json.dumps(body), headers=headers)
    # loggers.info(f'request sent to user service for information about user : {player}')
    if response.status_code != 200:
        raise ValueError(f"responce error {response.status_code}")
    val = json.loads(response.content)
    return val.get('id')

def create_matches(tourn: Tournament, matche=None):
    players = tourn.trn_players.all()
    won_players = [plyr for plyr in players if plyr.won]
    if len(won_players) == 1:
        if matche:
            trn_m_count = tourn.matches.all().count()
            if trn_m_count != 3:
                handle_matche_required(matche)
                pass
        tourn.status = Tourn_status.EN.value
        tourn.save()
        return False
    p1 = None
    p2 = None
    i = 1
    for p in won_players:
        if i % 2 == 1:
            p1 = p
        else:
            p2 = p
            create_matche(p1, p2, tourn)
        i += 1
    return True


def handle_matche_required(matche1: Matche):
    try:
        trn = matche1.tourn
        trn_matches =  Matche.objects.filter(tourn=trn)
        for m in trn_matches:
            if m.id != matche1.id:
                matche2 = m
                break
        if matche2 is None:
            return
        new_matche = create_matche(matche2.winner, matche1.winner, trn)
        trn_m_count = Matche.objects.filter(tourn=trn).count()
        if trn_m_count != 3:
            return
        matche_res = {
            'p1_score': 0,
            'p2_score': 5,
            'winner': 2,
            'id': new_matche.pk,
        }
        save_matche(matche_res)
        rmPlayer_fromGame_service(matche1.winner.profile_id, matche2.winner.profile_id)
    except Exception as e:
        pass


#abid added this
def send_Request_to_Game_service(p1, p2, trnpk, mtchpk):
    url = 'http://game:8000/api/create/'
    data = {
        'm_id': mtchpk,
        't_id': trnpk,
        'player1' : p1.profile_id,
        'player2' : p2.profile_id,
        'gametype'    : "tourn",
    }
    # sends name
    res = requests.post(url=url,json=data)
    # print(res)
    return res


def create_matche(p1, p2, trn, create_game=True):
    matche = Matche.objects.create(tourn=trn)
    matche.player1 = p1
    matche.player2 = p2
    matche.round = trn.round
    matche.status = M_status.UNP.value
    matche.save()
    # abid added this

    if create_game:
        send_Request_to_Game_service(p1, p2, trn.pk,matche.pk)
    # print("create matche", flush=True)
    return matche



def send_match_start(trn: Tournament):
    channel_layer = get_channel_layer()
    group_name = f'trnGroup_{trn.pk}'
    response = generate_matche_response(trn)
    # print('send_match_start to : ', group_name, flush=True)
    async_to_sync(channel_layer.group_send)(
        group_name,
        {
            "type": "start_matche",
            "response": response,
        }
    )


def is_round_finish(matche: Matche):
    tourn = matche.tourn
    matches = tourn.matches.filter(round=matche.round)
    end_matche = matches.filter(status=M_status.PLY.value)
    if matches.count() == end_matche.count():
        return True
    return False


def save_matche(matche_res):
    m_id = matche_res['id']
    p1_score = matche_res['p1_score']
    p2_score = matche_res['p2_score']
    matche = Matche.objects.get(id=m_id)
    winner_id = matche.player1.profile_id
    if matche_res['winner'] == 2:
        winner_id = matche.player2.profile_id
    trn = matche.tourn

    # critical part of code
    with transaction.atomic():
        matche = Matche.objects.select_for_update().get(id=m_id)
        if matche.status == M_status.UNP.value:
            matche.status = M_status.PLY.value
            matche.save()
            if matche_res['winner'] == 1:
                matche.winner = matche.player1
                matche.player2.won = False
                loser_id = matche.player2.profile_id
            else:
                matche.winner = matche.player2
                matche.player1.won = False
                loser_id = matche.player1.profile_id

            # update redis
            redis_instance = redis.StrictRedis.from_url(settings.CACHES['default']['LOCATION'])
            sufix = "to_not_invite"
            redis_instance.delete(f'{sufix}_{loser_id}')
            if matche.round == Round.FN.value:
                redis_instance.delete(f'{sufix}_{winner_id}')
            redis_instance.close()

            matche.p1_score = p1_score
            matche.p2_score = p2_score
            # print('Matche result: ', p1_score, " | ", p2_score, flush=True)
            matche.player1.goals_achieved += p1_score
            matche.player1.goals_received += p2_score
            matche.player2.goals_achieved += p2_score
            matche.player2.goals_received += p1_score
            matche.player1.save()
            matche.player2.save()
            matche.save()

            # print('after matche save', flush=True)
            _new_round = False
            if is_round_finish(matche):
                new_round(matche)
                if trn.status == Tourn_status.EN.value:
                    _new_round = False 
                _new_round = True
            return {'new_round': _new_round, 'trn': trn, 'winner_id': winner_id}
    _new_round = False
    if trn.round == Round.FN.value:
        _new_round = True
    return {'new_round': _new_round, 'trn': trn, 'winner_id': winner_id}



def update_round(trn : Tournament):
    if trn.round == Round.FN.value:
        return
    trn.round = Round.FN.value
    trn.save()


def new_round(matche: Matche):
    trn = matche.tourn
    update_round(trn)
    create_matches(trn, matche)
    send_match_start(trn)
    return trn

def player_left(player: Player):
    try:
        trn = player.tournament
        matche = trn.matches.all().filter(Q(player1=player)|Q(player2=player),
            status=M_status.UNP.value).latest('id')
        if matche:
            win1 = (player.profile_id == matche.player2.profile_id)
            win2 = (player.profile_id == matche.player1.profile_id)
            openent_id = matche.player1.profile_id
            if win2:
                openent_id = matche.player2.profile_id
            matche_res = {
                'p1_score': 5*win1,
                'p2_score': 5*win2,
                'winner': win1*1+win2*2,
                'id': matche.pk,
            }
            # print('GAME RESULT: ============== :\n', matche_res, flush=True)
            save_matche(matche_res)
            rmPlayer_fromGame_service(openent_id, player.profile_id)
            send_matchend(trn, matche, matche_res, openent_id)
    except Exception as e:
        if player:
            player.won = False
            player.save()
            rmPlayer_fromGame_service(-1, player.profile_id)
        # print('EXCEPTION IN player_left(): ', e, flush=True)
        pass


def rmPlayer_fromGame_service(openent_id, player_id):
        data = {
            'id1': openent_id,
            "id2":player_id,
        }
        url = 'http://game:8000/api/remove_game/'

        # send REOVE GAME
        res = requests.post(url=url,json=data)
        # print(f'REMOVE INGame REsponse : {res.text}', flush=True)


def send_matchend(trn, matche, m_res, openent_id):
    channel_layer = get_channel_layer()
    group_name = f'trnGroup_{trn.pk}'
    matche_res = {
        'p1score': m_res['p1_score'],
        'p2score': m_res['p2_score'],
        'winer': m_res['winner'],
        'id': matche.pk,
    }
    async_to_sync(channel_layer.group_send)(
        group_name,
        {
            "type": "matche_end",
            "user_id": openent_id,
            "matche_res": matche_res,
        }
    )


def generate_matche_response(trn: Tournament):
    matches = Matche.objects.filter(tourn=trn, round=trn.round)
    trn_matches = []
    if trn.status == Tourn_status.ST.value:
        for m in matches:
            trn_matches.append({
                'id': m.pk,
                'p1_img':m.player1.img_url,
                'p1_name':m.player1.name,
                'p1_id':m.player1.profile_id,
                'p2_img':m.player2.img_url,
                'p2_name':m.player2.name,
                'p2_id':m.player2.profile_id,
                'status': m.status,
                'create_time': m.created_at.isoformat(),
            })
    resp_data = {
        'type': 'matche',
        'refresh': 'false',
        'matches': trn_matches,
        'trn_name': trn.name,
        'trn_id': trn.id, 
    }
    return resp_data
    
