#!/bin/bash

CPP_BRIDGE_V5_SOURCE="$( cd "$(dirname "$BASH_SOURCE")/.." ; pwd -P )"

echo CPP_BRIDGE_V5_SOURCE = $CPP_BRIDGE_V5_SOURCE

cd $CPP_BRIDGE_V5_SOURCE

mkdir build
cd build

cmake .. && cmake --build .

./cpp_bridge_v5_app_executable -t

