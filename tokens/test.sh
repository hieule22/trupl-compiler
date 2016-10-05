#!/bin/bash
## Script to compile and execute test suites.

## All test targets.
declare -a array=( \
        "token_test" \
	"keyword_token_test" \
	"punctuation_token_test" \
	"rel_operator_token_test" \
	"add_operator_token_test" \
	"mul_operator_token_test" \
	"identifier_token_test" \
	"number_token_test" \
	"eof_token_test" \
)
## Test targets to run.
TARGET=$1

## GoogleTest options.
GTEST_ARGS="--test_output=all --nocache_test_results"

## Compile and execute tests.
if [ $TARGET == "all" ]
then
    for test in "${array[@]}"
    do
	make $test && ./$test $GTEST_ARGS
    done
else
    make $TARGET && ./$TARGET $GTEST_ARGS
fi

## Clean-up.
make clean && cd ../scanner/ && make clean
