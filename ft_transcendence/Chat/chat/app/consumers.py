from channels.generic.websocket import WebsocketConsumer
from asgiref.sync import async_to_sync
import django
django.setup()

from .models import Message
import json

class ChatConsumer(WebsocketConsumer):
    def connect(self):
        self.user = self.scope.get("user")
        if not self.user.get("user_id"):
            self.close()
        else:
            self.accept()

    def receive(self, text_data):
        if not self.user.get("user_id"):
            self.close()
            return
        try:
            data = json.loads(text_data)
        except json.JSONDecodeError:
            self.send(text_data=json.dumps({"error": "Invalid JSON format"}))
            return
        type = data['type']
        user_id = data['user_id']
        if type == 'start':
            self.create_roomName(user_id)
        if type == 'msg_isRead':
            msg_id = data['msg_id']
            self.msg_isRead(msg_id)
        if type == 'all_unread_msgs':
            self.all_unread_msgs(user_id)
 
    def create_roomName(self, user_id):
        self.room_group_name = f'chat_{user_id}'
        # print("last_player added to group: {}".format(
        #     self.room_group_name), flush=True)
        async_to_sync(self.channel_layer.group_add)(
            self.room_group_name,
            self.channel_name,
        )

    def msg_isRead(self, msg_id):
        msg = Message.objects.get(id=msg_id)
        msg.is_read = True
        msg.save()
    
    def all_unread_msgs(self, user_id):
        all_unread_msgs = Message.objects.filter(receiver_id=user_id,
            is_read=False)
        self.send(text_data=json.dumps({
            'type': 'unread_msgs',
            'all_unread_msgs': all_unread_msgs,
        }))



    def new_msg(self, event):
        msg_text = event['msg_text']
        sender_id = event['sender_id']
        receiver_id = event['receiver_id']
        msg_id = event['msg_id']
        unread_msgs = event['unread_msgs']
        all_unread_msgs = event['all_unread_msgs']
        _type = event['_type']
        self.send(text_data=json.dumps({
            'type': _type,
            'sender_id': sender_id,
            'receiver_id': receiver_id,
            'msg_text': msg_text,
            'msg_id': msg_id,
            'unread_msgs': unread_msgs,
            'all_unread_msgs': all_unread_msgs,
        }))
        
    def block(self, event):
        block = event['block']
        other_uid = event['other_uid']
        
        self.send(text_data=json.dumps({
            'type': 'block',
            'block': block,
            'other_uid': other_uid,
        }))




    def disconnect(self, close_code):
        # print("a user is rmoved from group", flush=True)
        if hasattr(self, 'room_group_name'):    
            async_to_sync(self.channel_layer.group_discard)(
                self.room_group_name,
                self.channel_name,
            )