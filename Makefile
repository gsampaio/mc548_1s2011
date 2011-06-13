CC = gcc
OPT = -Wall -Wextra -g `pkg-config --libs --cflags eina` -lm
SRC_FILES = src/main.c
LIB_FILES = lib/point.c lib/problem.c lib/solution.c lib/station.c
INCLUDE_DIR = include
BIN = saveWorld

TEST_PROBLEM = tests/problem.c
BIN_TEST_PROBLEM = tests/problemTest

TEST_STATION = tests/station.c
BIN_TEST_STATION = tests/stationTest

TEST_POINT = tests/points.c
BIN_TEST_POINT = tests/pointTest

TEST_SOLUTION = tests/solution.c
BIN_TEST_SOLUTION = tests/solutionTest

save_world:
	${CC} ${SRC_FILES} ${LIB_FILES} -o ${BIN} -I${INCLUDE_DIR} ${OPT}

test:
	${CC} ${TEST_PROBLEM} ${LIB_FILES} -o ${BIN_TEST_PROBLEM} -I${INCLUDE_DIR} ${OPT}
	${CC} ${TEST_STATION} ${LIB_FILES} -o ${BIN_TEST_STATION} -I${INCLUDE_DIR} ${OPT}
	${CC} ${TEST_POINT} ${LIB_FILES} -o ${BIN_TEST_POINT} -I${INCLUDE_DIR} ${OPT}
	${CC} ${TEST_SOLUTION} ${LIB_FILES} -o ${BIN_TEST_SOLUTION} -I${INCLUDE_DIR} ${OPT}

clean:
	rm -f src/*~ ${BIN}
