#! /bin/bash

g++ ./src/file_operations.cpp ./src/kryptosolver.cpp ./src/test_functions.cpp ./src/tests.cpp -o ./test_files/run_tests
cd test_files
./run_tests
cd ..
