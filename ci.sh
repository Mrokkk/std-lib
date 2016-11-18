#!/bin/bash

set -x
set -e

mkdir -p build
cd build
case $1 in
    ut )
        if [[ $COVERAGE ]]; then
            cmake .. -DCOVERAGE=ON
        else
            cmake ..
        fi
        if [[ $VALGRIND ]]; then
            make
            valgrind ./yacppl
        else
            if [[ $COVERAGE ]]; then
                make tests-cov
            else
                make tests-run
            fi
        fi
esac

