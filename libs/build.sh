#!/usr/bin/env bash

declare CC=gcc
declare STD=
declare FLG="-Wall -Wextra -Wfatal-errors -fshort-enums"
declare OPT="-O0" # if you want to use "-Ofast" add "-fno-fast-math" too (and if using clang add also "-Wno-overriding-t-option")
declare INC=./include
declare SRC=./src
declare BIN=./bin
declare TST=./tests
declare EXT=
declare SFX=
declare OUT="tests_output.txt"
declare MEM=

function CLEAN() {
    echo Removing files from $BIN directory.
    rm -rf $BIN/*
}

if [[ "$1" == "clean" ]]; then
    CLEAN
    exit
fi

function RUN_TEST() {
    $MEM $BIN/$@ >> $OUT
}

function RUN_TESTS() {
    RUN_TEST ce_test
    RUN_TEST meh_test
    RUN_TEST gem_methods_test
    RUN_TEST gem_memcb_test
    RUN_TEST gem_lambda_test
    RUN_TEST gem_linux_test
    RUN_TEST kewl_test
    RUN_TEST gest_pfssysnfo_test
    RUN_TEST werks_ansi_test
    RUN_TEST werks_strhashgroup_test
    RUN_TEST werks_expreval_test
    RUN_TEST werks_log_test
    RUN_TEST werks_dynvoke_test
    RUN_TEST werks_fileread_test
    RUN_TEST werks_stringlist_test
    RUN_TEST werks_kvm_test
    RUN_TEST werks_randomness_test
    RUN_TEST werks_i18n_test
    RUN_TEST werks_program_test
    RUN_TEST perks_multiplatform_test
    RUN_TEST perks_dbgmm_test
    RUN_TEST perks_signals_test
}

function TEST() {
    echo Running tests from $BIN directory.
    touch $OUT
    RUN_TESTS
    cat $OUT | awk '{ gsub(" OK", "\033[1;32m&\033[0m"); gsub("ERROR", "\033[1;31m&\033[0m"); print }' | grep -e '@test_end' -e 'ERROR'
    rm -f $OUT
}

# | GREP_COLOR='1;32' grep --color=always 'ERROR-FREE' | grep --colour=always 'ERRORS'
if [[ "$1" == "test" ]]; then
    TEST
    exit
fi

if [[ "$1" == "testmem" ]]; then
    MEM="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes"
    if [[ "$2" == "" ]]; then
        echo No test specified.
    else
        if [[ "$3" != "" ]]; then
            MEM+=" --log-file=$3"
        fi
        RUN_TEST $2
        rm -f $OUT
    fi
    exit
fi

if [[ "$1" == "debug" ]]; then
    echo Debug information is being included.
    EXT+="-g "
fi

function MODE() {
    STD=$@
    echo Compiling with $CC in $STD standard mode:
}

function MAKE_TEST() {
    echo "  $BIN/$1"
    rm -f $BIN/$1
    $CC -std=$STD $FLG $OPT -I$INC -I$SRC -o $BIN/$@ $EXT $TST/$1.c $SFX # 2>> $BIN/build-output.txt
}

function BUILD() {
    if [ ! -d "$BIN" ]; then
      mkdir -p "$BIN"
    fi

    # NOTE: if you set the mode to gnu11, you can compile everything (all features) with no additional defines

    # NOTE: -pedantic-errors enabled whenever is possible

    # CE

    echo \#define CE $(date +%Y%m%d)L > $INC/ce_version-inc.h
    MODE c89 # to get all the function pointers you need to compile at least with c99
    MAKE_TEST ce_test -pedantic-errors

    # MEH & GEM

    MODE c99
    MAKE_TEST meh_test # this implies compiling ce with all the function pointers too
    if [[ "$CC" == "clang" ]]; then
        SFX=" -lBlocksRuntime -fblocks"
        MAKE_TEST gem_memcb_test -pedantic-errors
        MAKE_TEST gem_lambda_test -pedantic-errors -Wno-gnu-statement-expression
        MAKE_TEST gem_methods_test -pedantic-errors -Wno-gnu-statement-expression
        SFX=""
    else
        MAKE_TEST gem_memcb_test
        MAKE_TEST gem_lambda_test
        MAKE_TEST gem_methods_test -Wno-unknown-pragmas # for ignoring clang pragmas present in the test
    fi
    MAKE_TEST gem_linux_test -pedantic-errors

    # KEWL & GEST

    MAKE_TEST gest_pfssysnfo_test $SRC/gest_pfssysnfo.c -pedantic-errors # for unix-like only
    EXT+=$SRC/kewl.c # from now on, everything uses kewl
    MAKE_TEST kewl_test -D_POSIX_C_SOURCE=200809L # the posix 93 activation is for some DATETIME's features, and posix 01 will be even better due to optimizations in the code, and posix 08 for a feature of CMDLINE

    # WERKS & PERKS

    MAKE_TEST werks_dynvoke_test $SRC/werks_dynvoke.c -rdynamic -ldl -D_GNU_SOURCE # all required by dynvoke to work
    MAKE_TEST werks_ansi_test $SRC/werks_ansi.c -pedantic-errors
    MAKE_TEST werks_strhashgroup_test $SRC/werks_strhashgroup.c -pedantic-errors
    MAKE_TEST werks_expreval_test $SRC/werks_expreval.c -pedantic-errors
    MAKE_TEST werks_i18n_test $SRC/werks_i18n.c -pedantic-errors
    MAKE_TEST werks_kvm_test $SRC/werks_kvm.c -pedantic-errors
    MAKE_TEST werks_stringlist_test $SRC/werks_stringlist.c
    MAKE_TEST werks_fileread_test $SRC/werks_fileread.c -pedantic-errors
    MAKE_TEST werks_log_test $SRC/werks_log.c -pedantic-errors
    MAKE_TEST werks_randomness_test $SRC/werks_randomness.c -pedantic-errors -D_POSIX_C_SOURCE=200809L # the posix 08 activation is for the secure random bytes
    MAKE_TEST werks_program_test $SRC/werks_program.c -pedantic-errors -D_POSIX_C_SOURCE=199309L # the posix 93 activation is for nap usage in the test program
    MAKE_TEST perks_signals_test $SRC/perks_signals.c -pedantic-errors -D_POSIX_C_SOURCE=200809L # the posix 08 activation is for the SA_RESTART inclusion
    MODE c11 # required by multiplatform to get echo and by dbgmm (besides it compiles under c99) to get the aligned_alloc
    MAKE_TEST perks_dbgmm_test $SRC/perks_dbgmm.c -pedantic-errors
    MAKE_TEST perks_multiplatform_test $SRC/perks_multiplatform.c -D_POSIX_C_SOURCE=1 # the test requires the posix version of the stdout redirection
}

BUILD
TEST
echo Done.

