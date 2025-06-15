from django.db import models
from django.utils import timezone 
from django.contrib.auth.models import User

class Profile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE,default=1)
    avatar = models.ImageField(default='default.jpg', upload_to='profile_images')
    friends = models.ManyToManyField('self', blank=True, symmetrical=True)
    remote_user = models.BooleanField(default=False)
    ruser_id = models.IntegerField(default=-1)
    tournament_name = models.CharField(max_length=100,null=True,blank=True)
    is_online = models.BooleanField(default=False)
    def __str__(self):
        if self.user:
            return self.user.username
        else:
            return 'No associated user'
        
class Friend_Request(models.Model):
    sender = models.ForeignKey(Profile, related_name='sender', on_delete=models.CASCADE)
    receiver = models.ForeignKey(Profile, related_name='reciver', on_delete=models.CASCADE)
    timestamp = models.DateTimeField(default=timezone.now)
    
    def __str__(self):
        return f"{self.sender.user.username} -&gt; {self.receiver.user.username}"

class Notification(models.Model):
    message = models.CharField(max_length=100, blank=True, null=True) 
    user = models.ForeignKey(User, on_delete=models.CASCADE,default=1)
    timestamp = models.DateTimeField(default=timezone.now)
    is_read = models.BooleanField(default=False)
    def __str__(self):
        return self.message
