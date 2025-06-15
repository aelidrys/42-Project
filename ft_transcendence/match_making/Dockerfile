FROM python:3.8

RUN apt-get update \
	&& apt-get install -y --no-install-recommends \
		postgresql-client \
	&& rm -rf /var/lib/apt/lists/*

ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1

COPY requirements.txt /app/

WORKDIR /app

EXPOSE 8000

RUN pip install --upgrade pip && \
    pip install -r requirements.txt

RUN rm -f requirements.txt

# COPY ./service .

CMD ["bash","./script.sh"]