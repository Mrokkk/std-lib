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
            valgrind ../bin/std_lib
        else
            ../bin/std_lib
        fi
        if [[ $COVERAGE ]]; then
            make coverage
        fi ;;
esac

