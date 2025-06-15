FROM python:3.11

RUN apt update -y && apt upgrade -y

RUN apt install -y python3-django 

COPY ./requirements.txt /user/app/requirements.txt

RUN  pip install -r /user/app/requirements.txt

RUN python3 -m pip install Pillow

RUN python -m pip install -U 'channels[daphne]'

RUN pwd

EXPOSE 8000

WORKDIR /user/app

RUN cd /user/app

CMD ["bash", "./script.sh"]
