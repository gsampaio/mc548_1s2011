#!/bin/bash

cd ../
echo "Compiling tests"
cd -
./problemTest ../instances/teste
./stationTest ../instances/teste
./pointTest
./solutionTest ../instances/teste
