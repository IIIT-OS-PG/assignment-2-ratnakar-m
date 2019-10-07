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
	src/client/client_of_tracker/tracker_comm.cpp \
	src/client/client_of_tracker/commands_menu.cpp \
	src/client/client_of_tracker/cli_commands_impl.cpp \
	src/client/peer_as_client/download_impl.cpp \
	src/client/peer_as_client/peer_comm.cpp \
	src/client/peer_as_service/peer_listener.cpp \
	src/client/peer_as_service/commands_handler.cpp \
	src/client/peer_util.cpp \
	src/common/network_util.cpp \
	src/common/commons_util.cpp \
	src/common/hash_util.cpp \

LIBS = -lpthread -lcrypto -ljsoncpp

build:
	@mkdir -p bin && \
	g++ -g -w  -std=c++0x  $(TRACKER_SRC) -I $(COMMON_INCLUDES) -I $(TRACKER_INCLUDES) -o $(EXEC_TRACKER) $(LIBS) && \
	chmod +x $(EXEC_TRACKER) && \
	mkdir -p demo_space/tracker && \
	cp $(EXEC_TRACKER) demo_space/tracker
	@g++ -g -w -std=c++0x  $(CLIENT_SRC) -I $(COMMON_INCLUDES) -I $(CLIENT_INCLUDES) -o $(EXEC_CLIENT) $(LIBS) && chmod +x $(EXEC_CLIENT) && \
	chmod +x $(EXEC_CLIENT) && \
        mkdir -p demo_space/peer1 && \
        mkdir -p demo_space/peer2 && \
        mkdir -p demo_space/peer3 && \
        cp $(EXEC_CLIENT) demo_space/peer1 && \
        cp $(EXEC_CLIENT) demo_space/peer2 && \
        cp $(EXEC_CLIENT) demo_space/peer3


run: build
	./$(EXEC)

debug: build
	gdb $(EXEC)

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC_TRACKER)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC_CLIENT)

