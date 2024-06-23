#!/bin/bash

# Variables
CXX=g++
CXXFLAGS="-std=c++11 -Wall -Wextra"
SRC="src/main.cpp"  # Only source files here
OUTDIR="cmake-build-debug"
EXEC="$OUTDIR/MyVector"

# Create output directory if it doesn't exist
mkdir -p $OUTDIR

# Compile
$CXX $CXXFLAGS $SRC -o $EXEC

echo "Build completed"