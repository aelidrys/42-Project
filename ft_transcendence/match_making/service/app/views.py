from django.shortcuts import render
from django.http import HttpResponse
from rest_framework.views import APIView
from django.template.loader import get_template
from django.core.cache import cache
from .models import queue
from django.core.serializers import serialize
import json


def clear_queue(request):
    var = queue.objects.all()
    count = len(var)
    var.delete()
    return HttpResponse(f"{count} deleated from queue table")

def get_queue(request):
    var = queue.objects.all()
    return HttpResponse(serialize('json', var), content_type='application/json')

class in_queue(APIView):
    def post(self, request):
        data = json.loads(request.body)
        if not queue.objects.filter(socket_id=data.get("channel_id")):
            return HttpResponse("FALSE")
        else:
            return HttpResponse("TRUE")


class quit_queue(APIView):
    def post(self, request):
        data = json.loads(request.body)
        ele = queue.objects.filter(socket_id=data.get("channel_id"))
        ele.delete()
        return HttpResponse("deleted")
    

class match_maker(APIView):
    def get(self, request):
        res = {
            "cmd" : "wait",
            "player1": None,
            "player2": None
        }
        data = queue.objects.order_by("joined_at")[:2]
        if len(data) == 2:
            res["cmd"] = "make"
            res["player1"] = data[0].socket_id
            res["player2"] = data[1].socket_id
        
        return HttpResponse(json.dumps(res))

class put_in_queue(APIView):
    def get(self, request):
        return HttpResponse("working...")

    def post(self, request):
        var = queue()
        self.KEYNAME = "match_maker_queue"
        try:
            body = request.body.decode('utf-8')
            data = json.loads(body)
            id = data.get("channel_id")
            name = data.get("login")  
        except json.JSONDecodeError as e:
            return HttpResponse("Invalid JSON data: " + str(e), status=400)
        
        var.socket_id = id
        var.login = name
        var.save()
        res = {
            "cmd" : "wait",
            "player1": None,
            "player2": None
        }
        data = queue.objects.order_by("joined_at")[:2]
        if len(data) == 2:
            res["cmd"] = "make"
            res["player1"] = data[0].socket_id
            res["player2"] = data[1].socket_id
        
        return HttpResponse(json.dumps(res))


def get_view(request):
    return render(request,"view.html")
