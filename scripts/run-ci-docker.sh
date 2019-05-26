#!/bin/bash

set -e

CPP_BRIDGE_V5_SOURCE="$( cd "$(dirname "$BASH_SOURCE")/.." ; pwd -P )"

echo CPP_BRIDGE_V5_SOURCE = $CPP_BRIDGE_V5_SOURCE

cd $CPP_BRIDGE_V5_SOURCE

mkdir build || echo build folder already exists
cd build

export CMAKE_GCOV_ENABLED=true

cmake .. && cmake --build .

./cpp_bridge_v5_app_executable -tl

echo lcov -e coverage.all.info -o coverage.info "$CPP_BRIDGE_V5_SOURCE/*"

lcov -c -d . -o coverage.all.info
lcov -e coverage.all.info -o coverage.info "$CPP_BRIDGE_V5_SOURCE/*"
genhtml coverage.info --output-directory gcov-html

