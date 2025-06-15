
import jwt
from datetime import datetime
from rest_framework import authentication, exceptions
from django.conf import settings


class CustomJWTAuthentication(authentication.BaseAuthentication):
    def authenticate(self, request):
        authorization_heaader = request.headers.get('Authorization')
        if not authorization_heaader:
            raise exceptions.AuthenticationFailed("Authorization header missing.")
        try:
            access_token = authorization_heaader.split(' ')[1]
            payload = jwt.decode(
                access_token, settings.SECRET_KEY, algorithms=['HS256'])
            user_id = payload.get("user_id")  
            return ({"user_id": user_id}, None) 
        except jwt.ExpiredSignatureError:
            raise exceptions.AuthenticationFailed('Access token expired')
        except jwt.InvalidTokenError:
            raise exceptions.AuthenticationFailed('Invalid token format or signature')
        except IndexError:
            raise exceptions.AuthenticationFailed('Token prefix missing')  
        except Exception as e:
            raise exceptions.AuthenticationFailed(f'Authentication error: {str(e)}') 