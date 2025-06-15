from django.apps import AppConfig


class UsercontentConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'usercontent'


    def ready(self):
        import usercontent.signals