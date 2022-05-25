#!/bin/bash

# Syntax: build.sh -d [ROOT_DIRECTORY] -m [ debug | release ]

while getopts d:m:h flag
do
  case "$flag" in
    d) directory=${OPTARG};;
    m) mode=${OPTARG};;
    h)
      echo "Syntax: build.sh -d [ROOT_DIRECTORY] -m [ debug | release ]"
      exit 0
      ;;
    *)
      echo "Invalid flag '$flag'"
      exit 1
      ;;
  esac
done

if [ "" = "${directory}" ];
then
  echo "Error: No directory provided. Try 'build.sh -h' for more information."
  exit 1
fi

if [ "" = "${mode}" ];
then
  echo "Error: No build mode specified. Try 'build.sh -h' for more information."
  exit 1
fi

if [ ! -d "${directory}" ];
then
  echo "Error: '${directory}' doesn't exist or isn't a directory."
  exit 1
fi

case "$mode" in
  "debug")
    echo "cmake --build ./cmake-build-debug --target dsvcol -j 9"
    cmake --build ./cmake-build-debug --target dsvcol -j 9
    echo "[Build finished]"
    ;;
  "release")
    echo "cmake --build ./cmake-build-release --target dsvcol -j 9"
    cmake --build ./cmake-build-release --target dsvcol -j 9
    echo "[Build finished]"
    ;;
  *)
    echo "Invalid build mode '$mode'"
    exit 1
    ;;
esac
