from django.urls import path
from . import views

urlpatterns = [
    path('api/register/', views.register, name='register'),
    path('api/profile/<int:pk>/', views.Profileview.as_view(), name='profile_user'),
    path('api/profile/', views.ProfileList.as_view(), name='profile'),
    path('api/myprofile/', views.MyProfileList.as_view()),
    path('api/protected/', views.ProtectedData.as_view()),
    path('api/userupdate/', views.UserDetail.as_view()),
    path('api/frequest/', views.FriendRequestList.as_view()),
    path('api/addfriend/<int:pk>/', views.CreateFriendRequest.as_view()),
    path('api/acceptfriend/<int:pk>/', views.ManageFriendRequest.as_view()),
    path('api/notifications/', views.NotificationList.as_view()),
    path('api/deletefriend/<int:pk>/', views.FriendDetails.as_view()),
    path('api/notif/<int:pk>/', views.NotifictionDetails.as_view()),
    path('api/changepassword/<int:pk>/', views.ChangePassword.as_view()),
    path('api/logout/', views.LogoutView.as_view()),
]