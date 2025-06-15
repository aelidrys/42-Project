from django.contrib import admin
from .models import Tournament, Player
from .matches import Matche

admin.site.register(Tournament)
admin.site.register(Matche)
admin.site.register(Player)
