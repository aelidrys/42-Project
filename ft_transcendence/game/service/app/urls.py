from django.urls import path, include
from . import views

# included in path("api/", include("app.urls")),
urlpatterns = [
    # path("", views.test),
    path("create/", views.creat_game),
    # path("is_ingame/", views.is_in_game.as_view()),
    path("stats/", views.getstats),
    # path("delete_game/", views.delete_game),
    path("remove_game/", views.remove_game)
    
]