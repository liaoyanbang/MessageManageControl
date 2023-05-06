#!/bin/bash

rm cmake-build-debug -r
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
./main

