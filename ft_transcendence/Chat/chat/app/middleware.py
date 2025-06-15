
import jwt
from jwt.exceptions import ExpiredSignatureError, InvalidTokenError
from channels.db import database_sync_to_async
from django.conf import settings

from channels.middleware import BaseMiddleware

class JWTAuthMiddleware(BaseMiddleware):

    async def __call__(self, scope, receive, send):
        headers = dict(scope['headers'])
        token = self.get_access_token(headers=headers)
        
        if token:
            try:
                decoded_token = jwt.decode(
                    token,
                    settings.SECRET_KEY,
                    algorithms=['HS256']
                )
                scope['user'] = {"user_id": decoded_token.get("user_id")}
            except ExpiredSignatureError:
                await self._close_with_error(send, "Token expired", 4001)
                return
            except InvalidTokenError:
                await self._close_with_error(send, "Invalid token", 4002)
                return
            except Exception as e:
                # print(f"Unexpected error: {e}", flush=True)
                await self._close_with_error(send, "Unexpected error", 4003)
                return
        else:
            await self._close_with_error(send, "Authorization header missing", 4000)
            return
        return await super().__call__(scope, receive, send)
    
    async def _close_with_error(self, send, message, code):
        # print(f"WebSocket closed: {message} (code: {code})", flush=True)
        await send({
            "type": "websocket.close",
            "code": code
        })
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