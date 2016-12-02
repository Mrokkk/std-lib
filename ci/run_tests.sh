#!/bin/bash

set -e

dir=$(dirname $0)

cd $dir/..
mkdir -p build
cd build

cores=$(nproc)

case "$JOB" in
    "valgrind")
        cmake ..
        make -j$cores
        valgrind ./yacppl ;;
    "coverage")
        cmake -DCOVERAGE=ON ..
        make tests-cov -j$cores ;;
    "sanitizers")
        cmake -DSANITIZERS=ON ..
        make tests-run -j$cores ;;
    *)
        cmake ..
        make tests-run -j$cores ;;
esac

