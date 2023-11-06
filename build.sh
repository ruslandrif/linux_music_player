#!/bin/bash
mkdir build
cd build/
cmake ../ 
make
chmod +s Player
./Player