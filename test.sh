#!/bin/bash
cd ToolChain
make clean
make all
cd ..
make clean
make all
./run.sh