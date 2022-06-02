add_custom_target(all-tests)
add_dependencies(all-tests
        ischrin.test
        delimiter_optarg.test
        getline.test
        dsvcol
        )


add_executable(ischrin.test EXCLUDE_FROM_ALL
        ischrin.test.c ../src/util.c ../include/util.h
        )

add_executable(delimiter_optarg.test EXCLUDE_FROM_ALL
        delimiter_optarg.test.c
        ../src/delimiter_optarg.c ../include/delimiter_optarg.h
        ../src/util.c ../include/util.h
        )

add_executable(getline.test EXCLUDE_FROM_ALL
        getline.test.c
        ../src/getline.c ../include/getline.h
        )
