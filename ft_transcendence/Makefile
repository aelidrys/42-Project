FILES =	-f "./docker-compose.yml"  

all:
	docker-compose up --build

up:
	docker compose $(FILES) up -d

down:
	docker compose $(FILES) down

restart:
	docker compose $(FILES) restart

start:
	docker compose $(FILES) start

stop:
	docker compose $(FILES) stop

build:
	docker compose $(FILES) build
	