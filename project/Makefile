EXEC_TRACKER = tracker/tracker
EXEC_CLIENT = client/client

LIBS = -lpthread -lcrypto

COMMON_INCLUDES = ./commons/
CLIENT_INCLUDES = ./client
TRACKER_INCLUDES = ./tracker

TRACKER_SRC = \
	tracker/tracker_main.cpp  \
	tracker/commands_handler.cpp \
	tracker/commands_impl.cpp \
	commons/network_util.cpp \
	commons/commons_util.cpp \

CLIENT_SRC = \
	client/client_main.cpp \
	client/tracker_comm.cpp \
	client/peer_request_handler.cpp \
	client/commands_menu.cpp \
	client/commands_impl.cpp \
	commons/network_util.cpp \
	commons/commons_util.cpp \

build:
	g++ -g -w  -std=c++0x  $(TRACKER_SRC) -I $(COMMON_INCLUDES) -I $(TRACKER_INCLUDES) -o $(EXEC_TRACKER) $(LIBS) && chmod +x $(EXEC_TRACKER) 
	g++ -g -w -std=c++0x  $(CLIENT_SRC) -I $(COMMON_INCLUDES) -I $(CLIENT_INCLUDES) -o $(EXEC_CLIENT) $(LIBS) && chmod +x $(EXEC_CLIENT) 


run: build
	./$(EXEC)

debug: build
	gdb $(EXEC)

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

