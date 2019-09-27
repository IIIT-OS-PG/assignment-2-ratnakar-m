EXEC_SERVER = server
EXEC_SERVER2 = server2 #multiple clients can connect. infinite lopp in server
EXEC_SERVER3 = server3 #file dowload
EXEC_SERVER4 = server4 #request handling in a separate thread
EXEC_CLIENT = client
EXEC_CLIENT3 = client3

LIBS = -lpthread

INCLUDES = .

SERVER_SRC = \
	server.cpp 
SERVER2_SRC = \
	server2.cpp 
SERVER3_SRC = \
	server3.cpp 
SERVER4_SRC = \
	server4.cpp 
CLIENT_SRC = \
	client.cpp
CLIENT3_SRC = \
	client3.cpp

build:
	g++ -g -w -std=c++0x  $(SERVER_SRC) -I $(INCLUDES) -o $(EXEC_SERVER) $(LIBS) && chmod +x $(EXEC_SERVER) 
	g++ -g -w -std=c++0x  $(SERVER2_SRC) -I $(INCLUDES) -o $(EXEC_SERVER2) $(LIBS) && chmod +x $(EXEC_SERVER2) 
	g++ -g -w -std=c++0x  $(SERVER3_SRC) -I $(INCLUDES) -o $(EXEC_SERVER3) $(LIBS) && chmod +x $(EXEC_SERVER3) 
	g++ -g -w -std=c++0x  $(SERVER4_SRC) -I $(INCLUDES) -o $(EXEC_SERVER4) $(LIBS) && chmod +x $(EXEC_SERVER4) 
	g++ -g -w -std=c++0x  $(CLIENT_SRC) -I $(INCLUDES) -o $(EXEC_CLIENT) $(LIBS) && chmod +x $(EXEC_CLIENT) 
	g++ -g -w -std=c++0x  $(CLIENT3_SRC) -I $(INCLUDES) -o $(EXEC_CLIENT3) $(LIBS) && chmod +x $(EXEC_CLIENT3) 
	#g++ -g -w  $(SRC) -I $(INCLUDES) -o $(EXEC) $(LIBS) && chmod +x $(EXEC) 

run: build
	./$(EXEC)

debug: build
	gdb $(EXEC)

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

docker:
	docker run --workdir $(PWD) --rm --volume $(PWD):$(PWD) -it gcc bash
