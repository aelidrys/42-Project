from django.db import models
from django.utils import timezone
# Create your models here.




class Chat(models.Model):
    user1_id = models.IntegerField(default=0)
    user2_id = models.IntegerField(default=0)
    chat_id = models.IntegerField(default=0)
    blocker = models.IntegerField(default=-1)
    last_update =  models.DateTimeField(default=timezone.now)
    block = models.BooleanField(default=False)


class Message(models.Model):
    created_at = models.DateTimeField(default=timezone.now)
    msg_text = models.CharField(max_length=10000)
    receiver_id = models.IntegerField(default=-1)
    sender_id = models.IntegerField(default=-1)
    chat = models.ForeignKey(Chat, on_delete=models.CASCADE,
        related_name='messages')
    is_read = models.BooleanField(default=False)