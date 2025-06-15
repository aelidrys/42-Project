import os

from channels.routing import ProtocolTypeRouter, URLRouter
from django.core.asgi import get_asgi_application
from channels.auth import AuthMiddlewareStack
from app.routing import ws_urlpatterns
from app.middleware import JWTAuthMiddleware


os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'chat.settings')
django_asgi_app = get_asgi_application()

application = ProtocolTypeRouter({
    "http": get_asgi_application(),
    "websocket": JWTAuthMiddleware(URLRouter(ws_urlpatterns)),
})

