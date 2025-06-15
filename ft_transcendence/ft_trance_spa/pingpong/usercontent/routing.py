from django.urls import path
from . import consumers

websocket_urlpatterns = [
    path('ws/notf/', consumers.NotificationConsumer.as_asgi()),
]