from django.db import models
from .enums import Round, Tourn_status, M_status
from django.utils import timezone


class Tournament(models.Model):
    name = models.CharField(default="four players", max_length=50)
    status = models.CharField(choices=Tourn_status.choices(), max_length=50,
        default=Tourn_status.PN.value)
    round = models.CharField(choices=Round.choices, max_length=50,
        default=Round.HF.value)
    create_date = models.DateTimeField(default=timezone.now)
    size = models.IntegerField(default=4)
    created_at = models.DateTimeField(default=timezone.now)
    def __str__(self):
        return self.name

class Player(models.Model):
    name = models.CharField(max_length=100, default='player_x')
    username = models.CharField(max_length=100, null=True)
    tournament = models.ForeignKey(Tournament, on_delete=models.CASCADE,
        related_name="trn_players")
    profile_id = models.IntegerField(default=0)
    img_url = models.URLField(null=True)
    won = models.BooleanField(default=True)
    created_at = models.DateTimeField(default=timezone.now)
    goals_achieved = models.IntegerField(default=0)
    goals_received = models.IntegerField(default=0)
    def __str__(self):
        return self.name

class Matche(models.Model):
    tourn = models.ForeignKey(Tournament, on_delete=models.CASCADE,
        related_name="matches")
    round = models.CharField(max_length=50, default=Round.HF.value,
        choices=Round.choices())
    player1 = models.ForeignKey(Player, related_name="p1_matches",
        on_delete=models.CASCADE, null=True)
    player2 = models.ForeignKey(Player, related_name="p2_matches",
        on_delete=models.CASCADE, null=True)
    p1_score = models.IntegerField(default=0) 
    p2_score = models.IntegerField(default=0)
    winner = models.ForeignKey(Player, related_name="m_win",
        on_delete=models.CASCADE, null=True)
    status = models.CharField(max_length=50, default=M_status.UNP.value,
        choices=M_status.choices())
    created_at = models.DateTimeField(default=timezone.now)
    