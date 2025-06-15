from django.contrib.auth.models import User
from .models import Profile,Friend_Request ,Notification
from .serializer import UserSerializer ,UpdateUserSerializser,FriendRequestSerializer,NotificationSerializer,ProfileSerializer
from django.views.decorators.csrf import csrf_exempt
from django.http import HttpResponse
from django.http import Http404
import json

from rest_framework.response import Response
from rest_framework.decorators import api_view
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from rest_framework.permissions import IsAuthenticated, AllowAny
from rest_framework.decorators import api_view, permission_classes 
from rest_framework_simplejwt.authentication import JWTAuthentication

# hada rah ta3 lgame
@csrf_exempt
def getUser(request):
    if request.method == 'POST':
        try:
            body_unicode = request.body.decode('utf-8')
            body_data = json.loads(body_unicode)
            
            # Process the JSON data
            login = body_data.get('id', '')
            user = User.objects.get(id = login)
            prf = Profile.objects.get(user=user)
            res = {
                "id" : user.pk,
                "login" : user.username,
                "image" : prf.avatar.url,
            }

            return HttpResponse(json.dumps(res))
        except json.JSONDecodeError as e:
            return HttpResponse(f'Error decoding JSON: {str(e)}', status=400)
    else:
        return HttpResponse('Unsupported request method')


@api_view(['POST'])
@permission_classes([AllowAny])
def register(request):
    if request.method == 'POST':
        serializer = UserSerializer(data=request.data)
        if serializer.is_valid():
            user = serializer.save()
            return Response({"user": serializer.data}, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

def get_profile(user):
    try:
        return Profile.objects.get(user=user)
    except Profile.DoesNotExist:
        raise Http404("Profile not found")

class ProfileList(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]
    def get(self, request, format=None):
        profile = Profile.objects.all()
        serializer = ProfileSerializer(profile, many=True)
        return Response(serializer.data, status=status.HTTP_200_OK)
    


class MyProfileList(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]
    def get(self, request, format=None):
        profile = get_profile(request.user)
        serializer = ProfileSerializer(profile)
        return Response(serializer.data, status=status.HTTP_200_OK)

class UserDetail(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]

    def put(self, request, *args, **kwargs):
        user = request.user
        serializer = UpdateUserSerializser(user, data=request.data, partial=True)
        if serializer.is_valid():
            serializer.save()
            return Response(
                {
                    "message": "User data updated successfully.",
                    "updated_data": serializer.data
                },
                status=status.HTTP_200_OK
            )
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
class Profileview(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated] 
    def get_object(self, pk):
        try:
            return User.objects.get(pk=pk)
        except User.DoesNotExist:
            raise Http404("User not found")

    def get_profile(self, user):
        try:
            return Profile.objects.get(user=user)
        except Profile.DoesNotExist:
            raise Http404("Profile not found")
        
    def get(self, request,pk, format=None):
        user = self.get_object(pk)
        profile = self.get_profile(user)
        serializer = ProfileSerializer(profile)
        return Response(serializer.data)

    def put(self, request, pk, format=None):
        user = self.get_object(pk)
        profile = self.get_profile(user)
        serializer = ProfileSerializer(profile, data=request.data,partial=True)
        if serializer.is_valid():
            serializer.save()
            return Response({"success": "Profile updated successfully!"}, status=status.HTTP_200_OK)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class ProtectedData(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]
    def get(self, request):
        content = {'message': 'Hello, This is valid!'}
        return Response(content)
    
def user_friends(request):
    profile = get_profile(request.user)
    user_friends = profile.friends.all()
    return user_friends

class FriendRequestList(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]
    def get(self, request, format=None):
        current_user_profile = get_profile(user=request.user)
        try:
            all_friend_requests = Friend_Request.objects.filter(receiver=current_user_profile)
            all_friend_requests_send = Friend_Request.objects.filter(sender=current_user_profile)
            serializer = FriendRequestSerializer(all_friend_requests, many=True)
            serializer_send = FriendRequestSerializer(all_friend_requests_send, many=True)
            return Response({"ireceive": serializer.data, "isend": serializer_send.data}, status=status.HTTP_200_OK)
        except Exception as e:
            return Response({"error": str(e)}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
class CreateFriendRequest(APIView):

    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]

    def post(self, request, pk, format=None):
        sender = get_profile(user=request.user)
        if sender.id == pk:
            return Response({'error': 'You cannot send a friend request to yourself.'}, status=status.HTTP_400_BAD_REQUEST)
        try:
            receiver = Profile.objects.get(id=pk)
            if sender in  receiver.friends.all():
                return Response({'error': f'You already friend with {receiver.user}.'}, status=status.HTTP_400_BAD_REQUEST)
            
            friend_request, created = Friend_Request.objects.get_or_create(
                sender=sender, receiver=receiver
            )
            if created:
                return Response({'success': f'Friend request sent successfully to {receiver.user}.'}, status=status.HTTP_201_CREATED)
            else:
                return Response({'info': f'Friend request already sent to {receiver.user}.'}, status=status.HTTP_200_OK)
        except Profile.DoesNotExist:
            return Response({'error': 'User not found.'}, status=status.HTTP_404_NOT_FOUND)
        except Exception as e:
            return Response({'error': str(e)}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)


def acceptFriend(friendRequest,userProfile):
    if friendRequest.receiver == userProfile:
        friendRequest.receiver.friends.add(friendRequest.sender)
        return True
    return False

class ManageFriendRequest(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]

    def post(self,request,pk,format=None):
        try:
            friend_request = Friend_Request.objects.get(id=pk)
        except Friend_Request.DoesNotExist:
            return Response({'error': 'Friend request not found.'}, status=status.HTTP_404_NOT_FOUND)
        
        pCurrentUser = get_profile(user=request.user)
        if (acceptFriend(friend_request,pCurrentUser)):
            friend_request.delete()
            return Response({'success': 'new friend added  successfully.'}, status=status.HTTP_201_CREATED)
        else:
            return Response({'error': 'You are not authorized to accept this friend request.'}, status=status.HTTP_403_FORBIDDEN)
    
    def delete(self,request,pk,format=None):
        try:
            friend_request = Friend_Request.objects.get(id=pk)
        except Friend_Request.DoesNotExist:
            return Response({'error': 'Friend request not found.'}, status=status.HTTP_404_NOT_FOUND)
        
        currentP = get_profile(request.user)
        if friend_request.receiver == currentP or friend_request.sender == currentP:
            friend_request.delete()
            return Response({'success': 'Friend request deleted successfully.'}, status=status.HTTP_200_OK)
        else:
            return Response({'error': 'You are not authorized to delete this friend request.'}, status=status.HTTP_403_FORBIDDEN)
    
class NotifictionDetails(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [AllowAny]
    
    def post(self,request,pk,format=None):
        try:
            notification = Notification.objects.get(id=pk,user=request.user)
        except Notification.DoesNotExist:
            return Response({'error': 'Notification not found.'}, status=status.HTTP_404_NOT_FOUND)
        
        serializer = NotificationSerializer(notification,data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    def delete(self,request,pk,format=None):
        try:
            notification = Notification.objects.get(id=pk,user=request.user)
            notification.delete()
            notifications = Notification.objects.filter(user=request.user)
            unread_count = notifications.filter(is_read=False).count()
            return Response({'message': 'Notifiation deleted successfully.' , "unread_count": unread_count}, status=status.HTTP_200_OK)
        except Notification.DoesNotExist:
            return Response({'error': 'Notification not found.'}, status=status.HTTP_404_NOT_FOUND)



class NotificationList(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]
    
    def get(self, request, format=None):
        try:
            notifications = Notification.objects.filter(user=request.user).order_by('-timestamp')
            unread_count = notifications.filter(is_read=False).count()
            serializer = NotificationSerializer(notifications, many=True)
            return Response({
                "notifications": serializer.data,
                "unread_count": unread_count
            }, status=status.HTTP_200_OK)
            
        except Notification.DoesNotExist:
            return Response({
                "error": "Notifications not found for the user."
            }, status=status.HTTP_404_NOT_FOUND)
        
        except Exception as e:
            return Response({
                "error": f"An unexpected error occurred: {str(e)}"
            }, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
class FriendDetails(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]

    def delete(self, request, pk, format=None):
        try:
            prfriend = Profile.objects.get(pk=pk)
            profile = Profile.objects.get(user=request.user)
        except Profile.DoesNotExist:
            return Response({'error': 'Profile not found.'}, status=status.HTTP_404_NOT_FOUND)       
        if prfriend in profile.friends.all():
            profile.friends.remove(prfriend)
            return Response({"success": "Friend removed successfully"}, status=status.HTTP_200_OK)
        else:
            return Response({'error': 'User is not in your friends list.'}, status=status.HTTP_400_BAD_REQUEST)
class ChangePassword(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]
    
    def put(self, request, pk, format=None):
        oldpassword = request.data['oldpassword']
        newpassword = request.data["newpassword"]
        try:
            user = User.objects.get(pk=pk)
        except User.DoesNotExist:
            return Response({'error': 'User  not found.'}, status=status.HTTP_404_NOT_FOUND)

        pr = get_profile(user)
        # print(pr.remote_user,flush=True)
        if pr.remote_user:
            return Response({'error': 'You Cannot Change Password Of this User.'}, status=status.HTTP_403_FORBIDDEN)

        if newpassword.strip() == "":
             return Response({'error':"Password cannot be blank or contain only spaces."}, status=400)

        if not user.check_password(raw_password=oldpassword):
            return Response({'error': 'Current password is not correct'}, status=400)
        
        if not (8 <= len(newpassword.strip())  <= 20):
            return Response({'error': 'Password must be 8-20 characters long.'}, status=400)
        user.set_password(newpassword)
        user.save()
        return Response({'success': 'password changed successfully'}, status=200)

class LogoutView(APIView):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]
    def post(self, request):
        response = Response({"message": "Logout successful"},status=200)
        response.delete_cookie('refresh_token', path='/')
        return response
