from django.urls import path
from . import views 

urlpatterns = [
    # test
    # path("", views.R_login, name="R_login"),
    # path("home", views.home, name="home"),
    # path("logout", views._logout, name="logout"),
    
    
    # Remote auth
    path("auth_intra", views.authorization_intra, name="auth_intra"),
    path("intra_authorize", views.intra_authorize, name="intra_authorize"),
    # path("afterauthorization", views.afterauthorization, name="afterauthorization"),
]
