from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync
from rest_framework.response import Response
from rest_framework_simplejwt.views import TokenRefreshView,TokenObtainPairView
from rest_framework import status
from rest_framework.response import Response

def create_notification(message, user_id):
    channel_layer = get_channel_layer()
    async_to_sync(channel_layer.group_send)(
        f"user_{user_id}",
        {
            'type': 'send_notification',
            'message': message,
        }
    )
class CustomTokenRefreshView(TokenRefreshView):
    def post(self, request, *args, **kwargs):
        request.data['refresh'] = request.COOKIES.get('refresh_token')
        return super().post(request, *args, **kwargs)

class MyTokenObtainPairView(TokenObtainPairView):
    def post(self, request, *args, **kwargs):
        response = super().post(request, *args, **kwargs)
        if response.status_code == status.HTTP_200_OK:
            refresh_token = response.data.get('refresh')
            response.set_cookie(
                'refresh_token',         
                refresh_token,          
                httponly=True,          
                samesite='Strict',      
                path='/',
                secure=True,
            )
            response.data.pop('refresh', None)
        return response
