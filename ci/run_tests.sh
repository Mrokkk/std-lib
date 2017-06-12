#!/bin/bash

set -e

dir=$(dirname $0)

cd $dir/..
mkdir -p build
cd build

cores=$(nproc)

case "$JOB" in
    "valgrind")
        cmake -DCI=ON ..
        make tests-valgrind -j$cores ;;
    "coverage")
        cmake -DCI=ON -DCOVERAGE=ON ..
        make tests-cov -j$cores ;;
    "sanitizers")
        cmake -DCI=ON -DSANITIZERS=ON ..
        make tests-run -j$cores ;;
    "thread_safe")
        cmake -DCI=ON -DSANITIZERS=ON ..
        make tests-thread_safe-run -j$cores ;;
    *)
        cmake -DCI=ON -DCPP_STD=${CPP_STD} ..
        make tests-run -j$cores ;;
esac

