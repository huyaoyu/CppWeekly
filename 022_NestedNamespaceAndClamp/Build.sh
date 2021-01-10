#!/bin/bash

g++ NestedNamespaces.cpp -std=c++17 -O3 -o RunNestedNamespace.exe
g++ Clamp.cpp -std=c++17 -O3 -I../includes -o RunClamp.exe
