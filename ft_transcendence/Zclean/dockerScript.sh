#!/bin/bash

# Stop all running containers
docker stop $(docker ps -qa)

# Remove all containers
docker rm $(docker ps -qa)

# Remove all images
docker rmi -f $(docker images -qa)

# Remove all volumes
docker volume rm $(docker volume ls -q)

# Remove all networks (excluding default networks)
docker network rm $(docker network ls -q | grep -v "bridge\|host\|none")

# Optionally, prune the system to remove any dangling data
docker system prune -af
docker volume prune -f

