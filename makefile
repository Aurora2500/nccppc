CC=clang++
CFLAGS= --std=c++20

all: client

client: obj/client.o
	${CC} -o $@ $^ ${CFLAGS} -lncurses

server: $(filter-out obj/client.o, $(OBJ))

obj/%.o: src/%.cpp obj
	${CC} -c -o $@ $< ${CFLAGS}

obj:
	mkdir -p $@