default:
	@echo "Launching in production mode..."
	@docker-compose up --build -d
	@echo "Containers have started in production mode!"
	@echo "Access your app here: http://localhost:8080"
	@echo "HTTPS access: https://localhost:8443"

clean:
	@echo "Performing total reset and cleanup..."
	@echo ""
	@docker-compose down -v --remove-orphans --rmi all
	@docker rmi -f $$(docker images -q) 2>/dev/null || true
	@docker system prune -a -f
	@docker volume prune -f
	@rm -rf backend/node_modules frontend/node_modules frontend/dist backend/dist
	@rm -rf backend/database.db backend/game_data.databaseClient
	@rm -rf backend/uploads/* 2>/dev/null || true
	@docker exec backend rm -rf /app/uploads 2>/dev/null || true
	@find backend -name "*.db" -delete 2>/dev/null || true
	@find backend -name "*database*" -delete 2>/dev/null || true
	@rm -f backend/package-lock.json frontend/package-lock.json
	@npm cache clean --force
	@echo "Total reset and cleanup completed!"
	@echo "Run 'make' to restart in production mode."
	@rm -f backend/.env

.PHONY: default clean
