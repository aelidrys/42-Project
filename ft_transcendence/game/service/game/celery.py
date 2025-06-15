
import os
from celery import Celery

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'game.settings')

app = Celery('game')
app.config_from_object('django.conf:settings', namespace='CELERY')
app.autodiscover_tasks()

# this if for debuggin
@app.task(bind=True)
def debug_task(self):
    print('Request: {0!r}'.format(self.request))