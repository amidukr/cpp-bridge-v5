#!/bin/bash

set -e

export CPP_BRIDGE_V5_SOURCE="$( cd "$(dirname "$BASH_SOURCE")/.." ; pwd -P )"
cd $CPP_BRIDGE_V5_SOURCE


./scripts/configure-docker.sh
./scripts/docker-build.sh


