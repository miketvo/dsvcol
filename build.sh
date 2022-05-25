#!/bin/bash

# Syntax: build.sh -d [ROOT_DIRECTORY] -m [ debug | release ]

while getopts d:m: flag
do
  case "$flag" in
    d) directory=${OPTARG};;
    m) mode=${OPTARG};;
    *)
      echo "Invalid flag '$flag'"
      exit 1
      ;;
  esac
done

if [ ! -d "${directory}" ];
then
  echo "Error: '${directory}' doesn't exist or isn't a directory."
  exit 1
fi

case "$mode" in
  "debug") cmake --build ./cmake-build-debug --target dsvcol -j 9;;
  "release") cmake --build ./cmake-build-release --target dsvcol -j 9;;
  *)
    echo "Invalid build mode '$mode'"
    exit 1
    ;;
esac
