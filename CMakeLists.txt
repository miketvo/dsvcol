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

# Black box test (negative)
add_test(main.test.errfile dsvcol ./thisfileshouldnotexist.file)
set_property(TEST main.test.errfile PROPERTY WILL_FAIL true)
add_test(main.test.badopt dsvcol -k)
set_property(TEST main.test.badopt PROPERTY WILL_FAIL true)
add_test(main.test.f.opt.nooptarg dsvcol -f)
set_property(TEST main.test.f.opt.nooptarg PROPERTY WILL_FAIL true)
add_test(main.test.format.opt.nooptarg dsvcol --format)
set_property(TEST main.test.format.opt.nooptarg PROPERTY WILL_FAIL true)
add_test(main.test.f.opt.badoptarg dsvcol -f dsv)
set_property(TEST main.test.f.opt.badoptarg PROPERTY WILL_FAIL true)
add_test(main.test.format.opt.badoptarg dsvcol --format dsv)
set_property(TEST main.test.format.opt.badoptarg PROPERTY WILL_FAIL true)
add_test(main.test.fd.exclusive dsvcol -f tsv -d ,)
set_property(TEST main.test.fd.exclusive PROPERTY WILL_FAIL true)
add_test(main.test.formatdelimiters.exclusive dsvcol --format tsv --delimiters ,)
set_property(TEST main.test.formatdelimiters.exclusive PROPERTY WILL_FAIL true)
add_test(main.test.d.opt.badoptarg dsvcol -d \\\;)
set_property(TEST main.test.d.opt.badoptarg PROPERTY WILL_FAIL true)
add_test(main.test.delimiters.opt.badoptarg dsvcol --delimiters \\\;)
set_property(TEST main.test.delimiters.opt.badoptarg PROPERTY WILL_FAIL true)
add_test(main.test.t.opt.qualifiercollision dsvcol -d \(\) -t \(\))
set_property(TEST main.test.t.opt.qualifiercollision PROPERTY WILL_FAIL true)
add_test(main.test.text-qualifier.opt.qualifiercollision dsvcol --delimiters \(\) --text-qualifier \(\))
set_property(TEST main.test.text-qualifier.opt.qualifiercollision PROPERTY WILL_FAIL true)
add_test(main.test.t.opt.toomanyqualifiers dsvcol -t '123')
set_property(TEST main.test.t.opt.toomanyqualifiers PROPERTY WILL_FAIL true)
add_test(main.test.text-qualifier.opt.toomanyqualifiers dsvcol --text-qualifier '123')
set_property(TEST main.test.text-qualifier.opt.toomanyqualifiers PROPERTY WILL_FAIL true)
add_test(main.test.l.opt.nooptarg dsvcol -l)
set_property(TEST main.test.l.opt.nooptarg PROPERTY WILL_FAIL true)
add_test(main.test.locale.opt.nooptarg dsvcol --locale)
set_property(TEST main.test.locale.opt.nooptarg PROPERTY WILL_FAIL true)

# Black box test (possitive)
add_test(main.test.noopts dsvcol ./test/data/bos2021ModC.csv)
add_test(main.test.f.opt.goodoptarg1 dsvcol -f csv ./test/data/bos2021ModC.csv)
add_test(main.test.f.opt.goodoptarg2 dsvcol -f tsv ./test/data/bos2021ModC.tsv)
add_test(main.test.d.opt.goodoptarg3 dsvcol -d | ./test/data/bos2021ModC.dat)
add_test(main.test.t.opt dsvcol -t \"\" ./test/data/bos2021ModC.csv)
add_test(main.test.ft.opt.goodoptarg1 dsvcol -f csv -t \"\" ./test/data/bos2021ModC.csv)
add_test(main.test.ft.opt.goodoptarg2 dsvcol -f tsv -t \"\" ./test/data/bos2021ModC.tsv)
add_test(main.test.dt.opt.goodoptarg3 dsvcol -d | -t \"\" ./test/data/bos2021ModC.dat)
