EXEC_TRACKER = bin/tracker
EXEC_CLIENT = bin/client

COMMON_INCLUDES = ./include//common/
CLIENT_INCLUDES = ./include/client
TRACKER_INCLUDES = ./include/tracker

TRACKER_SRC = \
	src/tracker/tracker_main.cpp  \
	src/tracker/commands_handler.cpp \
	src/tracker/commands_impl.cpp \
	src/tracker/tracker_util.cpp \
	src/common/network_util.cpp \
	src/common/commons_util.cpp \
	src/common/hash_util.cpp \

CLIENT_SRC = \
	src/client/client_main.cpp \
	src/client/tracker_comm.cpp \
	src/client/peer_request_handler.cpp \
	src/client/commands_menu.cpp \
	src/client/commands_impl.cpp \
	src/common/network_util.cpp \
	src/common/commons_util.cpp \
	src/common/hash_util.cpp \

LIBS = -lpthread -lcrypto -ljsoncpp

build:
	@mkdir -p bin && \
	g++ -g -w  -std=c++0x  $(TRACKER_SRC) -I $(COMMON_INCLUDES) -I $(TRACKER_INCLUDES) -o $(EXEC_TRACKER) $(LIBS) && \
	chmod +x $(EXEC_TRACKER) && \
	mkdir -p workspace/tracker && \
	cp $(EXEC_TRACKER) workspace/tracker
	@g++ -g -w -std=c++0x  $(CLIENT_SRC) -I $(COMMON_INCLUDES) -I $(CLIENT_INCLUDES) -o $(EXEC_CLIENT) $(LIBS) && chmod +x $(EXEC_CLIENT) && \
	chmod +x $(EXEC_CLIENT) && \
        mkdir -p workspace/peer1 && \
        mkdir -p workspace/peer2 && \
        mkdir -p workspace/peer3 && \
        cp $(EXEC_CLIENT) workspace/peer1 && \
        cp $(EXEC_CLIENT) workspace/peer2 && \
        cp $(EXEC_CLIENT) workspace/peer3


run: build
	./$(EXEC)

debug: build
	gdb $(EXEC)

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC_TRACKER)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC_CLIENT)

