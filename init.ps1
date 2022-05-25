# Initialize the project with the following CMake configurations

Write-Output "\ncmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S .\ -B ./cmake-build-debug"
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S ./ -B ./cmake-build-debug

Write-Output "\ncmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S .\ -B ./cmake-build-release"
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_C_COMPILER=gcc -G Ninja -S ./ -B ./cmake-build-release
