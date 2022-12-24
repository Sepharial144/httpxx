#!/bin/sh

cmake . -Bbuild -DCMAKE_BUILD_TYPE=Debug -G Ninja ..
cmake --build build