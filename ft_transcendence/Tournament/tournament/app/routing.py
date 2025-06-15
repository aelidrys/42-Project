from django.urls import re_path
from .consumers import WSConsumer, WSConsumer_trnInfo

ws_urlpatterns = [
    re_path(r'ws/tourn/', WSConsumer.as_asgi()),
    re_path(r'ws/tourn_info/', WSConsumer_trnInfo.as_asgi()),
]