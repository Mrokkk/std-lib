mkdir -p build
pushd build
cmake -DCMAKE_CXX_COMPILER=g++-6 ..
make
popd
./bin/std_lib
