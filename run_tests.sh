#! /bin/bash

g++ ./src/basic_functions.cpp ./src/file_operations.cpp ./src/codewordpuzzle.cpp ./src/test_functions.cpp ./src/tests.cpp -o ./test_files/run_tests
cd test_files
./run_tests
cd ..
