from django.db.models.signals import post_save
from django.contrib.auth.models import User
from django.dispatch import receiver
from .models import Notification,Friend_Request
from .models import Profile,Friend_Request
import os
import random
import string

from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync



def generate_random_suffix(length=10):
    return ''.join(random.choices(string.ascii_lowercase + string.digits, k=length))

def validate_tournament_name( value):
    while Profile.objects.filter(tournament_name=value).exists():
        value = f"{value}{generate_random_suffix()}"
    return value

@receiver(post_save, sender=User)
def create_profile(sender, instance, created, **kwargs):
    if created:
        trn_name = validate_tournament_name(f't_{instance.username}') 
        Profile.objects.create(user=instance,tournament_name=trn_name)

def notfCount(user):
        notifications =  Notification.objects.filter(user=user)
        unread_count = notifications.filter(is_read=False).count()
        return unread_count

@receiver(post_save, sender=Notification)
def notification_created(sender, instance, created, **kwargs):
    if created:
        channel_layer = get_channel_layer()
        room_name = f'user_{instance.user.id}'
        user_group_name = f"notification_{room_name}"
        profile = Profile.objects.get(user=instance.user)
        avatar_url = profile.avatar.url if profile.avatar else None
        timestamp_str = instance.timestamp.isoformat()
        size = notfCount(instance.user)
        async_to_sync(channel_layer.group_send)(
            user_group_name,
                  {
                "type": "send_notification",
                "message": instance.message,
                "avatar"  : avatar_url,
                "is_read" : instance.is_read,
                "size_notf":(size),
                "time": timestamp_str,
                "id": instance.id,  
                "_type": "message"
            }
        )
@receiver(post_save, sender=Friend_Request)
def create_friend_request_notification(sender, instance, created, **kwargs):
    if created:
        message = f" You have a new friend request from {instance.sender.user.username}"
        Notification.objects.create(user=instance.receiver.user, message=message)