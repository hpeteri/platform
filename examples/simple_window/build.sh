#!/bin/bash

PROJECT_NAME="simple_window"

WARNINGS="-Wformat=2 
          -Wmain 
          -Wparentheses 
          -Wuninitialized
          -Wsign-compare 
          -Werror"

LIBS="-lX11 -pthread -lGL ../../dependencies/GLEW/lib/libGLEW.a"
COMPILER_FLAGS=""
INCLUDE_FOLDERS="-I ../../src/ 
                 -I ../../dependencies/GLEW/include/
                 -I ./dependencies/"

pushd "$(dirname ${BASH_SOURCE[0]})"

if [ ! -d "build" ]
then
    mkdir build
fi

# command line arguments
if [[ $1 == "debug" ]]
then
    echo "debug build"
    COMPILER_FLAGS="-O0 $COMPILER_FLAGS"
    PREPROCESSOR="-g"
else
    echo "release build"
    COMPILER_FLAGS="-O3 $COMPILER_FLAGS"
    PREPROCESSOR="-s"
fi

gcc $PREPROCESSOR $COMPILER_FLAGS $WARNINGS $INCLUDE_FOLDERS "./src/main.c" -o "./build/main.a" $LIBS
popd

exit 0
