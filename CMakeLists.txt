cmake_minimum_required(VERSION 3.16)
project(dsvcol C)

set(CMAKE_C_STANDARD 11)

add_executable(dsvcol
        main.c
        include/glob.h
        src/util.c include/util.h
        src/delimiter_optarg.c include/delimiter_optarg.h
        )

enable_testing()
add_subdirectory(tests)
add_test(ischrin.test tests/ischrin.test)
add_test(delimiter_optarg.test tests/delimiter_optarg.test)
