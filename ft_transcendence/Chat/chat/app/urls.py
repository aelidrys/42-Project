from django.urls import path, include
from .views import chat, send_msg, chats
from .views import all_unread_msgs_view , block


urlpatterns = [
    path('', chat),
    path('send_msg', send_msg),
    path('chats', chats),
    path('all_unread_msgs', all_unread_msgs_view),
    path('block', block),
]
