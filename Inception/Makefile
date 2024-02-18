all:
	docker compose -f ./srcs/docker-compose.yml up -d --build  

down:
	docker compose -f ./srcs/docker-compose.yml down

down-all:
	docker-compose -f ./srcs/docker-compose.yml down

clean-all:
	@echo "This will delete the volumes 'mariadb' and 'wordpress'"
	@read -p "Are yuo sure? [yes/no] " answer; \
	if [ "$$answer" != "yes" ]; then \
		echo "operation cancled"; \
		exit 1; \
	fi
	docker-compose -f ./srcs/docker-compose.yml down \
	sudo rm -rf /home/aelidrys/data/mariadb/* \
	sudo rm -rf /home/aelidrys/data/wordpress/* \

re: down all 