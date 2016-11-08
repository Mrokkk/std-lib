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
        make
        if [[ $VALGRIND ]]; then
            valgrind ./std_lib
        else
            ./std_lib
        fi
        if [[ $COVERAGE ]]; then
            make coverage
        fi ;;
esac

