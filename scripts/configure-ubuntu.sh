#!/bin/bash

sudo apt update
sudo apt install --show-progress -y cmake build-essential libgtest-dev libgl-dev libglfw3-dev libglew-dev libeigen3-dev libopencv-dev git

mkdir googletest
cd googletest

git clone https://github.com/google/googletest.git
cd googletest
mkdir gbuild && cd gbuild && sudo cmake .. && sudo make install

