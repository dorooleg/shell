PROJECT_NAME := test
CPP_COMPILER := clang++
CPP_FLAGS 	 :=  -Werror -Wall -std=c++11 -O3 -Itests -Isrc
BUILD_DIR 	 := bin
SRC_DIR 	 := src
TEST_DIR 	 := tests


all: 
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/wc.cpp -o  ${BUILD_DIR}/wc
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/echo.cpp -o  ${BUILD_DIR}/echo
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/shell.cpp -o  ${BUILD_DIR}/shell
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/pwd.cpp -o  ${BUILD_DIR}/pwd
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/cat.cpp -o  ${BUILD_DIR}/cat
	
clean:
	rm -- ${BUILD_DIR}/*

.PHONY: clean all
