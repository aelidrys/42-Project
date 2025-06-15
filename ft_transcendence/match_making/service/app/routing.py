from django.urls import re_path
from .sockets import sockets
import os

ws_urlpatterns = [
    re_path(r'ws/queue/', sockets.as_asgi()),
]