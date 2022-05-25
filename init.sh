#!/bin/bash

# Initialize the project with the following CMake configurations

echo "cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S ./ -B ./cmake-build-debug"
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S ./ -B ./cmake-build-debug

echo "cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S ./ -B ./cmake-build-release"
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S ./ -B ./cmake-build-release
