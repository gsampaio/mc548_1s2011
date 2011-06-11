#!/bin/bash

cd ../
echo "Compiling tests"
make test
cd -
./problemTest ../instances/teste
./stationTest ../instances/teste
./pointTest
./solutionTest ../instances/teste
