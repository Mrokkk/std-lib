#!/bin/bash

set -e

docker run -t -v $PWD:$PWD $IMAGE /bin/bash -c "CXX=$COMPILER JOB=$JOB CPP_STD=$CPP_STD $PWD/ci/run_tests.sh"

