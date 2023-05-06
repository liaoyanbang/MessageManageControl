#!/bin/bash

rm cmake-build -r
mkdir cmake-build
cd cmake-build
cmake ..
make
./main

