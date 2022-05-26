cmake_minimum_required(VERSION 3.16)
project(dsvcol C)

set(CMAKE_C_STANDARD 11)

add_executable(dsvcol
        main.c
        include/glob.h
        src/util.c include/util.h
        src/delimiter_optarg.c include/delimiter_optarg.h
        )


##########################################
# TESTS                                  #
##########################################
enable_testing()
add_subdirectory(tests)

# Unit tests
add_test(ischrin.test tests/ischrin.test)
add_test(delimiter_optarg.test tests/delimiter_optarg.test)

# Black box tests
add_test(main.test.noopts dsvcol)
add_test(main.test.f.opt.goodoptarg1 dsvcol -f csv)
add_test(main.test.f.opt.goodoptarg2 dsvcol -f tsv)
add_test(main.test.d.opt.goodoptarg dsvcol -d \;)

# Black box tests (negative)
add_test(main.test.f.opt.nooptarg dsvcol -f)
set_property(TEST main.test.f.opt.nooptarg PROPERTY WILL_FAIL true)
add_test(main.test.f.opt.badoptarg dsvcol -f dsv)
set_property(TEST main.test.f.opt.badoptarg PROPERTY WILL_FAIL true)
add_test(main.test.fd.exclusive dsvcol -f tsv -d ,)
set_property(TEST main.test.fd.exclusive PROPERTY WILL_FAIL true)
add_test(main.test.d.opt.badoptarg dsvcol -d \\a)
set_property(TEST main.test.d.opt.badoptarg PROPERTY WILL_FAIL true)
