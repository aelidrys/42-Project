#/bin/sh
export DJANGO_SETTINGS_MODULE=game.settings
python manage.py makemigrations
python manage.py migrate

celery -A game worker --loglevel=info --detach
gunicorn game.asgi:application -b 0.0.0.0:8000 --worker-class uvicorn.workers.UvicornWorker
# python manage.py runserver 0.0.0.0:8000
# os.environ.setdefault("DJANGO_SETTINGS_MODULE", "your_project.settings")