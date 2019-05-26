#!/bin/bash

set -e

mkdir build || echo build folder already exists
cd build

export CMAKE_GCOV_ENABLED=true

cmake .. && cmake --build .

./cpp_bridge_v5_app_executable -tl

echo lcov -e coverage.all.info -o coverage.info "$CPP_BRIDGE_V5_SOURCE/*"

lcov -c -d . -o coverage.all.info
lcov -e coverage.all.info -o coverage.info "$CPP_BRIDGE_V5_SOURCE/*"
genhtml coverage.info --output-directory gcov-html



bash <(curl -s https://codecov.io/bash) -f coverage.info

