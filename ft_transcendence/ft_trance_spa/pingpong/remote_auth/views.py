from django.shortcuts import render, redirect
from django.contrib.auth.models import User
from django.contrib.auth import logout
from django.contrib import messages
from urllib.parse import urlencode
from .decorators import unauthentication_user, autenticated_only
from rest_framework.decorators import api_view, permission_classes
from rest_framework.permissions import IsAuthenticated, AllowAny

from django.http import HttpResponse
from django.http import JsonResponse
import os
import secrets
import requests
from django.core.files import File
from urllib.request import urlopen
from tempfile import NamedTemporaryFile
from django.core.exceptions import ValidationError
from usercontent.models import Profile
# from rest_framework import response
from rest_framework_simplejwt.tokens import RefreshToken
from rest_framework.response import Response
from usercontent.serializer import UserSerializer

import random
import string

def get_tokens_for_user(user):
    refresh = RefreshToken.for_user(user)
    return {
        'refresh_token': str(refresh),
        'access_token': str(refresh.access_token),
    }


# environment varibels
state = secrets.token_urlsafe(15)
client_id = os.environ.get('client_id')
redirect_uri = os.environ.get('redirect_uri')
client_secret = os.environ.get('client_secret')

# Remote authentication
# @unauthentication_user
def intra_authorize(request):
    
    # print("enter here remote \n")
    url = 'https://api.intra.42.fr/oauth/authorize'
    query_params = {
        'client_id': client_id,
        'redirect_uri': redirect_uri,
        'response_type': 'code',
        'scope': 'public',
        'state': state,
    }
    authorization_url = f"{url}?{urlencode(query_params)}"
    return redirect(authorization_url)

def exchange_data(code):
    token_url = "https://api.intra.42.fr/oauth/token"
    payload = {
        'grant_type': 'authorization_code',
        'client_id': client_id,
        'client_secret': client_secret,
        'code': code,
        'redirect_uri': redirect_uri,
    }
    response = requests.post(token_url, data=payload)
    post_data = response.json()
    return post_data

# download image of remote user from intra
def download_image_from_url(user_prf :Profile, image_link):
    try:
        # print("download_image_from_url enter",flush=True)
        img_temp = NamedTemporaryFile(delete=True)
        with urlopen(image_link) as img_link:
            img_temp.write(img_link.read())
            img_temp.flush()
        user_prf.avatar.save(f"image_{user_prf.pk}.jpg", File(img_temp))
        user_prf.save()
        # print("download_image_from_url call user_prf.save(), user_prf.avatar",user_prf.avatar,flush=True)
    except Exception as e:
        # print("Exception from download_image_from_url ===> ", e,flush=True)
        raise ValidationError(f"Failed to download image from {image_link}: {e}")



def getRandemUsername(username):
    s = ''.join(random.choices(string.ascii_lowercase + string.digits, k=5))
    return(f'{username}{s}')

def UsercreateORupdate(access_token, user_data):
    login = user_data.get('login')
    email = user_data.get('email')
    first_name = user_data.get('first_name')
    last_name = user_data.get('last_name')
    id = user_data.get('id')
    image_link = user_data.get('image')['link']
     
    userP = User.objects.filter(username=login).first()  
    if userP:  
        checkUsername = Profile.objects.filter(user=userP, remote_user=True).exists()
        useralready = Profile.objects.filter(ruser_id=id).first()

        if useralready:
            login = useralready.user.username  
        elif not checkUsername:
            check = True
            while check:
                login = getRandemUsername(login)  
                check = User.objects.filter(username=login).exists()

    created = None
    user_prf = Profile.objects.filter(ruser_id=id).first()
    if user_prf is None:           
        user, created = User.objects.get_or_create(username=login)
    if created: # create user from scrash
        user_prf = Profile.objects.get(user=user)
        user_prf.remote_user = True
        user_prf.ruser_id = id
        user.email = email
        user.first_name = first_name
        user.last_name = last_name
        download_image_from_url(user_prf, image_link)
        user_prf.save()
        user.save()
        # print(" after last download_image_from_url call user_prf.save(), user_prf.avatar",user_prf.avatar,flush=True)
    else:
        user = user_prf.user
    return(get_tokens_for_user(user))    



# @unauthentication_user
@api_view(['GET'])
@permission_classes([AllowAny])
def authorization_intra(request):
    code = request.GET.get('code')
    new_state = request.GET.get('state')
    if new_state == state:
        post_data = exchange_data(code)
        access_token = post_data.get('access_token')
        if access_token:
            user_data = fetch_data(access_token)
            tokens = UsercreateORupdate(access_token, user_data)
            response = JsonResponse({'access_token': tokens['access_token']})
            response.set_cookie(
                'refresh_token', 
                tokens['refresh_token'], 
                httponly=True, 
                samesite='Strict',    
                path='/',
                secure=True,         
            )
        return response
    return JsonResponse({'error': 'Invalid state or code'}, status=400)

def fetch_data(access_token):
    url = 'https://api.intra.42.fr/v2/me'
    headers = {
        'Authorization': f'Bearer {access_token}',
    }
    try:
        response = requests.get(url, headers=headers)
        response.raise_for_status()
    except:
        return None
    return response.json()

