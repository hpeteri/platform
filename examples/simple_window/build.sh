#!/bin/bash

PROJECT_NAME="simple_window"
OUTPUT_NAME="./build/$PROJECT_NAME"


LIBS+="-lX11 -pthread -lGL ../../dependencies/GLEW/lib/libGLEW.a "

OUTPUT_NAME+=".a"


WARNINGS="-Wformat=2 
          -Wmain 
          -Wparentheses 
          -Wuninitialized
          -Wsign-compare 
          -Werror"

COMPILER_FLAGS=""
INCLUDE_FOLDERS="-I ../../src/ 
                 -I ../../dependencies/GLEW/include/
                 -I ../../dependencies/"

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

time gcc $PREPROCESSOR $COMPILER_FLAGS $WARNINGS $INCLUDE_FOLDERS $LIBS "./src/main.c" -o $OUTPUT_NAME

popd

exit 0
