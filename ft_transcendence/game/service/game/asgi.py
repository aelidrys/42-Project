"""
ASGI config for game project.

It exposes the ASGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/3.2/howto/deployment/asgi/
"""

from channels.routing import ProtocolTypeRouter, URLRouter
from channels.security.websocket import AllowedHostsOriginValidator
from django.core.asgi import get_asgi_application
from app.middleware import JWTAuthMiddleware

from app.routing import ws_urlpatterns
import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'game.settings')

application = ProtocolTypeRouter({
    "http": get_asgi_application(),
    "websocket": JWTAuthMiddleware(URLRouter(ws_urlpatterns)),
})
