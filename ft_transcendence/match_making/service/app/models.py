from django.db import models
from datetime import datetime
from django.utils import timezone

class queue(models.Model):
    socket_id = models.CharField("socket", max_length=255, unique=True)
    player_id = models.IntegerField("player_id", blank=False, unique=True, default=-1)
    joined_at = models.DateTimeField("create date",  default=timezone.now)
    login = models.CharField("login", max_length=50, null=True)
    groupe = models.CharField("groupe", max_length=50,null= True)

