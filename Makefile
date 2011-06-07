CC = gcc
OPT = -Wall -Wextra `pkg-config --libs --cflags eina`
FILES = src/main.c include/save_world.h
INCLUDE_DIR = include
BIN = saveWorld

save_world:
	${CC} ${OPT} -I${INCLUDE_DIR} ${FILES} -o ${BIN}

clean:
	rm -f src/*~ ${BIN}
