import django
django.setup()
from django.contrib.auth.models import User
from django.contrib.auth.models import AnonymousUser

from channels.db import database_sync_to_async
from rest_framework_simplejwt.tokens import AccessToken, TokenError

@database_sync_to_async
def get_user(user_id):
    try:
        return User.objects.get(id=user_id)
    except User.DoesNotExist:
        return AnonymousUser()

class WebSocketJWTAuthMiddleware:
    def __init__(self, app):
        self.app = app

    async def __call__(self, scope, receive, send):
        headers = dict(scope['headers'])
        token = self.get_access_token(headers=headers)
        if token:
            try:
                access_token = AccessToken(token)
                scope["user"] = await get_user(access_token["user_id"])
            except TokenError:  
                scope["user"] = AnonymousUser()
            except Exception as e:
                scope["user"] = AnonymousUser()
        return await self.app(scope, receive, send)

    def get_access_token(self, headers):
        cookies = headers.get(b"cookie", b"").decode("utf-8")
        if not cookies:
            return None
        cookie_list = cookies.split("; ")
        cookie_dict = {}
        for item in cookie_list:
            if "=" in item: 
                key, value = item.split("=", 1)
                cookie_dict[key] = value
        return cookie_dict.get("access_token")    
