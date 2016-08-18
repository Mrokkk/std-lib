mkdir -p build
cd build
case $1 in
    build )
        cmake ..
        make ;;
    run_tests )
        if [[ $VALGRIND ]]; then
            valgrind ../bin/std_lib
        else
            ../bin/std_lib
        fi ;;
esac

