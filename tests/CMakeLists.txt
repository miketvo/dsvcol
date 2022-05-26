add_executable(ischrin.test
        ischrin.test.c ../src/util.c ../include/util.h
        )

add_executable(delimiter_optarg.test
        delimiter_optarg.test.c
        ../src/delimiter_optarg.c ../include/delimiter_optarg.h
        ../src/util.c ../include/util.h
        )
