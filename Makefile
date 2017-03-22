PROJECT_NAME := test
CPP_COMPILER := clang++
CPP_FLAGS 	 :=  -Werror -Wall -std=c++11 -O3 -Itests -Isrc
BUILD_DIR 	 := bin
SRC_DIR 	 := src
TEST_DIR 	 := tests


all: 
	mkdir -p ${BUILD_DIR}
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/wc.cpp -o  ${BUILD_DIR}/wc
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/echo.cpp -o  ${BUILD_DIR}/echo
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/shell.cpp ${SRC_DIR}/Environment.cpp ${SRC_DIR}/Preprocessor.cpp -o  ${BUILD_DIR}/shell
	${CPP_COMPILER} ${CPP_FLAGS} ${TEST_DIR}/tests.cpp ${SRC_DIR}/Environment.cpp ${SRC_DIR}/Preprocessor.cpp -o  ${BUILD_DIR}/tests
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/pwd.cpp -o  ${BUILD_DIR}/pwd
	${CPP_COMPILER} ${CPP_FLAGS} ${SRC_DIR}/cat.cpp -o  ${BUILD_DIR}/cat
	${CPP_COMPILER} ${CPP_FLAGS} -lboost_program_options ${SRC_DIR}/grep.cpp -o  ${BUILD_DIR}/grep
	
clean:
	rm -r -- ${BUILD_DIR}

.PHONY: clean all
