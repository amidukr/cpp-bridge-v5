#!/bin/bash

cd ~/cpp-bridge-v5

./scripts/configure-docker.sh

mkdir build
cd build

cmake .. && cmake --build .
