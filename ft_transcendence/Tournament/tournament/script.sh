#/bin/sh
echo "sleep 2 seconds"
sleep 2
python manage.py makemigrations
python manage.py migrate
echo '$$$$$$$$$$$$$ migrate finish $$$$$$$$$$$$$'
export DJANGO_SETTINGS_MODULE=tournament.settings
gunicorn tournament.asgi:application -b 0.0.0.0:8000 --worker-class uvicorn.workers.UvicornWorker

# python manage.py runserver 0.0.0.0:8000
echo '$$$$$$$$$$$$$ runserver finish $$$$$$$$$$$$$'
