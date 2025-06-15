from django.contrib.auth.models import User
from .models import Profile,Friend_Request,Notification
import os
from rest_framework import serializers
from rest_framework.validators import UniqueValidator

class UserSerializer(serializers.ModelSerializer):
    password1 = serializers.CharField(write_only=True, required=True)
    password2 = serializers.CharField(write_only=True, required=True)
    class Meta:
        model = User
        fields = ['id','username', 'email', 'password1', 'password2']
        
    def validate_username(self, username):
        username_ = username.lower().strip()
        if User.objects.filter(username__iexact=username_).exists():
            raise serializers.ValidationError( "Username already exists!")
        if len(username) < 3 or len(username) > 15:
            raise serializers.ValidationError('Username must be between 3 and 15 characters long')
        return username.lower()
    
    def validate(self, data):
        super().validate(data)  
        email = data.get("email").lower().strip()  
        if User.objects.filter(email__iexact=email).exists():
            raise serializers.ValidationError({"email": "Email already exists!"})  

        if not (8 <= len(data['password1'])  <= 20):
            raise serializers.ValidationError({
                'password1': "Password must be 8-20 characters long."
            })
        
        if data['password1'] != data['password2']:
            raise serializers.ValidationError({
                'password2': "Passwords do not match."
            })
        return data

    def create(self, validated_data):
        password = validated_data.pop('password1')
        validated_data.pop('password2')  
        user = User(**validated_data)
        user.set_password(password)  
        user.save()
        return user
    

class UpdateUserSerializser(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ['username', 'email']

    def validate_username(self, username):
        if len(username) < 3 or len(username) > 15:
            raise serializers.ValidationError('Username must be between 3 and 15 characters long')
        return username


class FriendSerializer(serializers.ModelSerializer):
    user = UserSerializer(read_only=True)
    class Meta:
        model = Profile
        fields = ['id','user', 'avatar', 'is_online']

class ProfileSerializer(serializers.ModelSerializer):
    user = UserSerializer(read_only=True)
    friends = FriendSerializer(many=True, read_only=True)  
    tournament_name = serializers.CharField(
    required=False,
    max_length=100,
    validators=[UniqueValidator(queryset=Profile.objects.all(), message="This tournament name is already taken.")]
    )
    class Meta:
        model = Profile
        fields = ['id','user', 'avatar',  'friends', 'remote_user', 'tournament_name','is_online']

    def validate_tournament_name(self, tournament_name):
        if len(tournament_name) < 3 or len(tournament_name) > 20:
            raise serializers.ValidationError('Tournament name must be between 3 and 20 characters long')
        return tournament_name
    
    def update(self, instance, validated_data):
        
        new_avatar = validated_data.get('avatar', None)
        tournament_name = validated_data.get('tournament_name', None)
        old_avatar = instance.avatar
        default_avatar_path = '/user/app/media/default.jpg'
        if new_avatar and old_avatar:
            if old_avatar.path != default_avatar_path and os.path.exists(old_avatar.path):
                os.remove(old_avatar.path)
        if new_avatar:
            instance.avatar = new_avatar
        if tournament_name:
            instance.tournament_name = tournament_name
        instance.save()
        return instance


class FriendRequestSerializer(serializers.ModelSerializer):
    sender = ProfileSerializer(read_only=True)
    receiver = ProfileSerializer(read_only=True)
    
    class Meta:
        model = Friend_Request
        fields = ["id","receiver","sender","timestamp"]


class NotificationSerializer(serializers.ModelSerializer):
    class Meta:
        model = Notification
        fields = ["id","is_read","message","timestamp"]