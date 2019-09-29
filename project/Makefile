EXEC_TRACKER = tracker/tracker
EXEC_CLIENT = client/client

LIBS = -lpthread -lcrypto

INCLUDES = ./commons/

TRACKER_SRC = \
	tracker/tracker_main.cpp  \
	commons/network_util.cpp \
	commons/commons_util.cpp
CLIENT_SRC = \
	client/client_main.cpp

build:
	g++ -g -w -std=c++14  $(TRACKER_SRC) -I $(INCLUDES) -o $(EXEC_TRACKER) $(LIBS) && chmod +x $(EXEC_TRACKER) 
	#g++ -g -w -std=c++0x  $(CLIENT_SRC) -I $(INCLUDES) -o $(EXEC_CLIENT) $(LIBS) && chmod +x $(EXEC_CLIENT) 


run: build
	./$(EXEC)

debug: build
	gdb $(EXEC)

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

