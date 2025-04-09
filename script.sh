#! /bin/bash


declare -r TESTS_RES_DIR="tests_res"
mkdir -p $TESTS_RES_DIR


# Run tests
make run compiler="g++" add_flags="-DCALC_NO_OPT -O0" run_flags="--tests=100" > $TESTS_RES_DIR/flags_opt_O0.txt
make clean

make run compiler="g++" add_flags="-DCALC_NO_OPT -O1" run_flags="--tests=100" > $TESTS_RES_DIR/flags_opt_O1.txt
make clean

make run compiler="g++" add_flags="-DCALC_NO_OPT -O2" run_flags="--tests=100" > $TESTS_RES_DIR/flags_opt_O2.txt
make clean

make run compiler="g++" add_flags="-DCALC_NO_OPT -O3" run_flags="--tests=100" > $TESTS_RES_DIR/flags_opt_O3.txt
make clean

make run compiler="g++" add_flags="-DCALC_NO_OPT -Ofast" run_flags="--tests=100" > $TESTS_RES_DIR/flags_opt_Ofast.txt
make clean


make run compiler="g++" add_flags="-DCALC_ARR_OPT -O3" run_flags="--tests=100" > $TESTS_RES_DIR/gcc_arr_opt.txt
make clean

make run compiler="clang++" add_flags="-DCALC_ARR_OPT -O3" run_flags="--tests=100" > $TESTS_RES_DIR/clang_arr_opt.txt
make clean


make run compiler="g++" add_flags="-DCALC_INTR128_OPT -O3" run_flags="--tests=100" > $TESTS_RES_DIR/intr128_opt.txt
make clean

make run compiler="g++" add_flags="-DCALC_INTR256_OPT -O3" run_flags="--tests=100" > $TESTS_RES_DIR/intr256_opt.txt
make clean


python calc_res.py
