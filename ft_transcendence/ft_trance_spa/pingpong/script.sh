#!/bin/bash
sleep 5

echo "Applying database migrations"
python manage.py makemigrations
python manage.py migrate


export DJANGO_SETTINGS_MODULE=pingpong.settings
gunicorn pingpong.asgi:application -b 0.0.0.0:8000 --worker-class uvicorn.workers.UvicornWorker

