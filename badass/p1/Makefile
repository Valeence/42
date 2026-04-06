.PHONY: build clean

build:
	docker build -t host-vandre -f host-vandre .
	docker build -t router-vandre -f router-vandre .
	@echo "Docker images ---------------------------------------------------"
	@docker images | grep vandre

clean:
	-docker rmi host-vandre
	-docker rmi router-vandre
