EXEC_SERVER = server
EXEC_CLIENT = client

LIBS = -lpthread -lcrypto

INCLUDES = .

SERVER_SRC = \
	server.cpp \
	utils.cpp

CLIENT_SRC = \
	client.cpp \
	utils.cpp

build:
	g++ -g -w -std=c++0x  $(SERVER_SRC) -I $(INCLUDES) -o $(EXEC_SERVER) $(LIBS) && chmod +x $(EXEC_SERVER) 
	g++ -g -w -std=c++0x  $(SERVER2_SRC) -I $(INCLUDES) -o $(EXEC_CLIENT) $(LIBS) && chmod +x $(EXEC_CLIENT) 

run: build
	./$(EXEC)

debug: build
	gdb $(EXEC)

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

docker:
	docker run --workdir $(PWD) --rm --volume $(PWD):$(PWD) -it gcc bash
