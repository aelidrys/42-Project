
FROM python:3.11

RUN apt update -y && apt upgrade -y

RUN apt install -y python3-django 

COPY ./requirements.txt /user/app/requirements.txt

RUN  pip install -r /user/app/requirements.txt

WORKDIR /user/app

EXPOSE 8000

# COPY ./script.sh /user/app
CMD ["bash", "./script.sh"]




