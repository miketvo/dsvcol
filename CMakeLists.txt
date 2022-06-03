cmake_minimum_required(VERSION 3.16)
project(dsvcol C)

set(CMAKE_C_STANDARD 11)

add_executable(dsvcol
        main.c
        include/glob.h
        src/util.c include/util.h
        src/delimiter_optarg.c include/delimiter_optarg.h
        src/dsv.c include/dsv.h
        src/getline.c include/getline.h
        )


##########################################
# TESTS                                  #
##########################################
enable_testing()
add_subdirectory(test)


# Unit test
add_test(ischrin.test test/ischrin.test)
add_test(delimiter_optarg.test test/delimiter_optarg.test)
add_test(getline.test test/getline.test)

# Black box test
add_test(main.test.noopts dsvcol ./test/data/bos2021ModC.csv)
add_test(main.test.f.opt.goodoptarg1 dsvcol -f csv ./test/data/bos2021ModC.csv)
add_test(main.test.f.opt.goodoptarg2 dsvcol -f tsv ./test/data/bos2021ModC.tsv)
add_test(main.test.d.opt.goodoptarg3 dsvcol -d | ./test/data/bos2021ModC.dat)

# Black box test (negative)
add_test(main.test.errfile dsvcol ./thisfileshouldnotexist.file)
set_property(TEST main.test.errfile PROPERTY WILL_FAIL true)
add_test(main.test.badopt dsvcol -k)
set_property(TEST main.test.badopt PROPERTY WILL_FAIL true)
add_test(main.test.f.opt.nooptarg dsvcol -f)
set_property(TEST main.test.f.opt.nooptarg PROPERTY WILL_FAIL true)
add_test(main.test.f.opt.badoptarg dsvcol -f dsv)
set_property(TEST main.test.f.opt.badoptarg PROPERTY WILL_FAIL true)
add_test(main.test.fd.exclusive dsvcol -f tsv -d ,)
set_property(TEST main.test.fd.exclusive PROPERTY WILL_FAIL true)
add_test(main.test.d.opt.badoptarg dsvcol -d \\\;)
set_property(TEST main.test.d.opt.badoptarg PROPERTY WILL_FAIL true)
