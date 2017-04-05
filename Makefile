PROJECT_NAME := test
CPP_COMPILER := clang++
CPP_FLAGS 	 := -MMD -Werror -lgtest -Wall -std=c++11 -O3 -Itests -Isrc
BUILD_DIR 	 := bin
SRC_DIR 	 := src
TEST_DIR 	 := tests

all: ${BUILD_DIR} ${BUILD_DIR}/shell ${BUILD_DIR}/echo ${BUILD_DIR}/wc ${BUILD_DIR}/pwd ${BUILD_DIR}/tests ${BUILD_DIR}/grep ${BUILD_DIR}/cat
	@echo "Done!"

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}/wc: ${SRC_DIR}/wc.cpp
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/wc.cpp -o  ${BUILD_DIR}/wc

${BUILD_DIR}/echo: ${SRC_DIR}/echo.cpp
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/echo.cpp -o  ${BUILD_DIR}/echo

${BUILD_DIR}/shell: ${SRC_DIR}/shell.cpp
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/shell.cpp ${SRC_DIR}/Environment.cpp ${SRC_DIR}/Preprocessor.cpp -o  ${BUILD_DIR}/shell

${BUILD_DIR}/tests: ${TEST_DIR}/tests.cpp
	${CPP_COMPILER} ${CPP_FLAGS} ${TEST_DIR}/tests.cpp ${SRC_DIR}/Environment.cpp ${SRC_DIR}/Preprocessor.cpp -o  ${BUILD_DIR}/tests

${BUILD_DIR}/pwd: ${SRC_DIR}/pwd.cpp
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/pwd.cpp -o  ${BUILD_DIR}/pwd

${BUILD_DIR}/cat: ${SRC_DIR}/cat.cpp
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/cat.cpp -o  ${BUILD_DIR}/cat

${BUILD_DIR}/grep: ${SRC_DIR}/grep.cpp
	${CPP_COMPILER} ${CPP_FLAGS} -lboost_program_options ${SRC_DIR}/grep.cpp -o  ${BUILD_DIR}/grep
	
clean:
	rm -r -- ${BUILD_DIR}

-include ${BUILD_DIR}/*.d

.PHONY: clean all
