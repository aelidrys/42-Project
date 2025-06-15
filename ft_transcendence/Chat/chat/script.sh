#/bin/sh
echo "sleep 2 seconds"
sleep 2
python manage.py makemigrations
python manage.py migrate
echo '$$$$$$$$$$$$$ migrate dqsd $$$$$$$$$$$$$'

export DJANGO_SETTINGS_MODULE=chat.settings
gunicorn chat.asgi:application -b 0.0.0.0:8000 --worker-class uvicorn.workers.UvicornWorker
# python manage.py runserver 0.0.0.0:8000
echo '$$$$$$$$$$$$$ runserver yes $$$$$$$$$$$$$'