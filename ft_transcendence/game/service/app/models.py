from django.db import models
from datetime import datetime
from django.utils import timezone

class Player(models.Model):
    player_id = models.IntegerField("player_id", blank=False, unique=True)
    login = models.CharField("player_id", max_length=50,unique=True)
    is_connected = models.BooleanField("is_connected",default=False)
    score = models.IntegerField("score",default= 0)
    channel_id = models.CharField("socket",null=True, max_length=255)
    side = models.IntegerField("side",default= 0)
    imageURL = models.CharField("imageURL", max_length=500, default="None")
    
    def __str__(self):
        return f"Player {self.login} (ID: {self.player_id}) - Score: {self.score} - Side: {self.side}"

class InGame(models.Model):
    player1 = models.ForeignKey(Player, related_name='player1', on_delete=models.CASCADE)
    player2 = models.ForeignKey(Player, related_name='player2', on_delete=models.CASCADE)
    groupName = models.CharField("groupName", max_length=200, default="None")
    created_at = models.DateTimeField("create_date", default=timezone.now)
    game_started = models.BooleanField("game_started",default= False)
    gametype = models.CharField("type", max_length=20, default="normal")
    gid = models.IntegerField("gid", default=-1)
    turnid = models.IntegerField("turnid", default=-1)

    def __str__(self):
        return f"InGame {self.groupName} - Players: {self.player1.login} vs {self.player2.login} - Game Started: {self.game_started}"

class PonGames(models.Model):
    gamename = models.CharField("gamename", max_length=50,default="")
    player1 = models.IntegerField("player1", blank=False, unique=False)
    player2 = models.IntegerField("player2", blank=False, unique=False)
    created_at = models.DateTimeField("create_date", default=timezone.now)
    goals_order =  models.CharField("goals_order", max_length=10, default="")
    p1goal = models.IntegerField("p1goal",default= 0)
    p2goal = models.IntegerField("p2goal",default= 0)
    winner = models.CharField("winner", max_length=50, default="")

    def __str__(self):
        return f"PonGame {self.gamename} - {self.player1} vs {self.player2} - Score: {self.p1goal}-{self.p2goal} - Winner: {self.winner}"

class PlayerStats(models.Model):
    player_id = models.IntegerField("player_id", blank=False, unique=False)
    games_played = models.IntegerField("games_played",default= 0)
    wins  = models.IntegerField("wins",default= 0)
    loss  = models.IntegerField("loss",default= 0)
    goals_scored  = models.IntegerField("goals_scored",default= 0)
    goals_conceded  = models.IntegerField("goals_conceded",default= 0)
    