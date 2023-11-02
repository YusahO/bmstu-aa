#!/bin/bash

cd prog
cmake -B build
cmake --build build -j 16
