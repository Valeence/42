# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vandre <vandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 17:53:16 by vandre            #+#    #+#              #
#    Updated: 2025/02/20 17:59:00 by vandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
DOCKER_COMPOSE_FILE = srcs/docker-compose.yml

# Cibles
.PHONY: up down build stop help ps

# Cible pour démarrer les services définis dans docker-compose.yml
up:
	@docker compose -f $(DOCKER_COMPOSE_FILE) up -d

# Cible pour arrêter les services définis dans docker-compose.yml
down:
	@docker compose -f $(DOCKER_COMPOSE_FILE) down
	@sudo docker system prune -a --volumes -f
	@sudo rm -rf /home/vandre/data

# Cible pour construire les images définies dans docker-compose.yml
build:
	@docker compose -f $(DOCKER_COMPOSE_FILE) build

# Cible pour arrêter les conteneurs définis dans docker-compose.yml
stop:
	@docker compose -f $(DOCKER_COMPOSE_FILE) stop

ps:
	@docker compose -f $(DOCKER_COMPOSE_FILE) ps

# Cible pour afficher l'aide
help:
	@echo "Makefile pour gérer docker-compose.yml"
	@echo ""
	@echo "Cibles disponibles:"
	@echo "  up      - Démarrer les services"
	@echo "  down    - Arrêter et supprimer les conteneurs, les réseaux, les images, et les volumes"
	@echo "  build   - Construire les images"
	@echo "  stop    - Arrêter les conteneurs"
	@echo "  help    - Afficher cette aide"
	@echo "  ps      - Afficher les conteneurs en cours d'exécution"
