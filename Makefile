CC = gcc
OPT = -Wall -Wextra `pkg-config --libs --cflags eina`
SRC_FILES = src/main.c
LIB_FILES = lib/point.c lib/problem.c lib/solution.c lib/station.c
INCLUDE_DIR = include
BIN = saveWorld

save_world:
	${CC} ${SRC_FILES} ${LIB_FILES} -o ${BIN} -I${INCLUDE_DIR} ${OPT}

clean:
	rm -f src/*~ ${BIN}
