#!/bin/bash

export DEBIAN_FRONTEND=noninteractive

apt update
apt upgrade -y
apt install -yy --show-progress cmake libgtest-dev libgl-dev libglfw3-dev libglew-dev libeigen3-dev libopencv-dev

