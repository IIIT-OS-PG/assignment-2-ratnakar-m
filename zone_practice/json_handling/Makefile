EXEC = json_test

LIBS = -lpthread -lcrypto -ljsoncpp

INCLUDES = .

SRC = \
	create_file_meta.cpp \

build:
	g++ -g -w  -std=c++0x  $(SRC) -I $(INCLUDES) -o $(EXEC) $(LIBS) && chmod +x $(EXEC) 


run: build
	./$(EXEC)

debug: build
	gdb $(EXEC)

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

