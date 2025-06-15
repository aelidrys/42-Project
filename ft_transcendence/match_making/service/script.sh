#/bin/sh
python manage.py makemigrations
python manage.py migrate

export DJANGO_SETTINGS_MODULE=main.settings
gunicorn main.asgi:application -b 0.0.0.0:8000 --worker-class uvicorn.workers.UvicornWorker

# python manage.py runserver 0.0.0.0:8000