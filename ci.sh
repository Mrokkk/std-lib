mkdir -p build
pushd build
cmake ..
make
popd
if [[ $VALGRIND ]]; then
    valgrind ./bin/std_lib
else
    ./bin/std_lib
fi
