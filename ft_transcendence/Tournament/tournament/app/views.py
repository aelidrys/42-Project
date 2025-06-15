from django.http import HttpResponse
from .models import Tournament, Matche, Player
from .tournament import tourn_subscribing, is_user_subscribe
from .tournament import send_tourn_info, _leave_trn, generate_tourn_response

from rest_framework.decorators import api_view
import json
from .enums import Round, Tourn_status, M_status
from .matches import save_matche
from django.db.models import Q
from .my_custom_auth import CustomJWTAuthentication
from rest_framework.decorators import api_view, authentication_classes


#abid zad hadi

from django.core.serializers import serialize
def tst(request):
    var1 = Tournament.objects.filter(Q(status=Tourn_status.PN.value) | Q(status=Tourn_status.ST.value))
    # var1 = Tournament.objects.all()
    # var2 = Matche.objects.all()
    # var3 = Player.objects.all()

    msg = {
        "stat": "working..",
        "Tournament": serialize('json', var1),
        "Matche": serialize('json', []),
        "Player": serialize('json', []),
    }
    var1.delete()
    return HttpResponse(json.dumps(msg), content_type='application/json')



@api_view(['POST'])
@authentication_classes([CustomJWTAuthentication])
def is_intorn(request):
    if request.method == 'POST':
        user_id = request.data['user']['id']
        plyr = is_user_subscribe(user_id)
        if plyr:
            response = {
                'intourn': 'yes',
                'trn_size': 4,
            }
        else:
            response = {
                'intourn': 'no',
                'trn_size': 0,
            }
        return HttpResponse(json.dumps(response),
            content_type='application/json')
    return (HttpResponse("la"))



@api_view(['POST'])
@authentication_classes([CustomJWTAuthentication])
def trn_subscribe(request):
    if request.method == 'POST':
        data = request.data
        trn = tourn_subscribing(data)
        send_tourn_info()
        if trn and trn.status == Tourn_status.ST.value:
            response = generate_matche_response(trn)
            return HttpResponse(json.dumps(response),
            content_type='application/json')

        players = generate_tourn_response(trn)
        return HttpResponse(json.dumps(players),
            content_type='application/json')


@api_view(['POST'])
@authentication_classes([CustomJWTAuthentication])
def leave_trn(request):
    if request.method == 'POST':
        data = request.data
        user_id = data['user']['id']
        response = _leave_trn(user_id)
        return HttpResponse(json.dumps(response),
            content_type='application/json')



def generate_matche_response(trn: Tournament):
    matches = Matche.objects.filter(tourn=trn, round=trn.round)
    trn_matches = []
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


@api_view(['GET'])
@authentication_classes([CustomJWTAuthentication])
def tourn_info(request):
    if request.method == 'GET':
        try:
            trn = Tournament.objects.latest('id')
            players = generate_tourn_response(trn)
            if trn.status == Tourn_status.PN.value:
                return HttpResponse(json.dumps(players),
                    content_type='application/json')
        except:
            pass
    return HttpResponse(json.dumps({'type':'tourn', 'created': False}),
        content_type='application/json')


def trn_history_response(trn: Tournament):
    matches = trn.matches.all().order_by('created_at')
    matche_list = []
    for matche in matches:
        matche_list.append({
            'p1': {
                'name': matche.player1.name,
                'img': matche.player1.img_url,
                'profile_id': matche.player1.profile_id,
                'score': matche.p1_score,
                'won': matche.winner == matche.player1,
            },
            'p2': {
                'name': matche.player2.name,
                'img': matche.player2.img_url,
                'profile_id': matche.player2.profile_id,
                'score': matche.p2_score,
                'won': matche.winner == matche.player1,
            },
            'round': matche.round,
        })
    response = {
        'status': 'ok',
        'trn_name': trn.name,
        'trn_id': trn.id,
        'size': trn.size,
        'matches': matche_list,
    }
    return response


def tourns_list(plyr_trns, pr_id):
    tourns = []
    for trn in plyr_trns:
        try:
            matche = trn.matches.get(round=Round.FN.value)
            won = pr_id == matche.winner.profile_id
        except:
            won = False
        date = str(trn.created_at.isoformat())[:10]
        tourns.append({
            'status': trn.status,
            'id': trn.id,
            'name': trn.name,
            'created_at': date,
            'won': won,
        })
    response = {
        'trns_len': len(tourns),
        'trns': tourns,
    }
    return response

@api_view(['POST', 'GET'])
@authentication_classes([CustomJWTAuthentication])
def tourn_history(request):
    if request.method == 'POST':
        data = request.data
        user_id = data['user']['id']
        plyr_trns = get_plyr_trns(user_id)
        response = tourns_list(plyr_trns, user_id)
        return HttpResponse(json.dumps(response),
            content_type='application/json')

    if request.method == 'GET':
        try:
            trn_id = int(request.GET.get('trn_id'))
            trn = Tournament.objects.get(id=trn_id)
        except:
            return HttpResponse(json.dumps({'status': 'ko'}),
                content_type='application/json')
        response = trn_history_response(trn)
        return HttpResponse(json.dumps(response),
            content_type='application/json')

    return HttpResponse(json.dumps({'status': 'ko'}),
            content_type='application/json')

def get_plyr_trns(user_id):
    players = Player.objects.filter(profile_id=user_id).order_by('-created_at')
    plyr_trns = []
    for plyr in players:
        if plyr.tournament.status == Tourn_status.EN.value:
            plyr_trns.append(plyr.tournament)
    return plyr_trns

@api_view(['POST', 'GET'])
@authentication_classes([CustomJWTAuthentication])
def trn_stats(request):
    if request.method == 'POST':
        data = request.data
        user_id = data['user']['id']
        # print("--->||",user_id,flush=True)
        players = Player.objects.filter(profile_id=user_id)
        wins = 0
        goals_achieved = 0
        goals_received = 0
        tourns_num = 0
        for plyr in players:
            if plyr.tournament.status != Tourn_status.EN.value:
                continue 
            if plyr.won:
                wins += 1
            tourns_num += 1
            goals_achieved += plyr.goals_achieved
            goals_received += plyr.goals_received
        return HttpResponse(json.dumps({'wins': wins, 'tourns_num': tourns_num,
            'goals_achieved': goals_achieved, 'goals_received': goals_received}),
            content_type='application/json')
    return HttpResponse(json.dumps({'wins': 0, 'tourns_num': 0}),
            content_type='application/json')


@api_view(['POST', 'GET'])
@authentication_classes([CustomJWTAuthentication])
def matchresult(request):
    if request.method == 'POST':
        try :
            data = json.loads(request.body)
            # print("game result recived\n", data, flush=True)
            response = save_matche(data)
            trn = response['trn']
            new_round = response['new_round']
            winner_id = response['winner_id']
        except Exception as e:
            # print('EXCEPTOIN: ', e, flush=True)
            return HttpResponse("error")
        trn_end = False
        if trn.status == Tourn_status.EN.value:
            trn_end = True
        return HttpResponse(json.dumps({'new_round': new_round, 'winner_id': winner_id,
            'trn_end': trn_end, 'trn_id': trn.pk}), content_type='application/json')
    return HttpResponse('allow only POST method')



@api_view(['POST', 'GET'])
@authentication_classes([CustomJWTAuthentication])
def matche_info(request):
    if request.method == 'POST':
        try:
            data = json.loads(request.body)
            m_id = data['matche_id']
            matche = Matche.objects.get(id=m_id)
            # print('Matche: ', matche, flush=True)
            return HttpResponse(json.dumps({'matche': {
                'm_id': matche.pk,
                'player1': matche.player1.name,
                'player2': matche.player2.name,
                'm_status': matche.status,
                'round': matche.round,
            }}),
            content_type='application/json')
        except:
            pass
    return HttpResponse(json.dumps({'m_status': 'None'}))
