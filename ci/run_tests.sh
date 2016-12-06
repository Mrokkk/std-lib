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
        make -j$cores
        valgrind ./tests/yacppl ;;
    "coverage")
        cmake -DCI=ON -DCOVERAGE=ON ..
        make tests-cov -j$cores ;;
    "sanitizers")
        cmake -DCI=ON -DSANITIZERS=ON ..
        make tests-run -j$cores ;;
    *)
        cmake -DCI=ON ..
        make tests-run -j$cores ;;
esac

