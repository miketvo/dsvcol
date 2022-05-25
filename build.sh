#!/bin/bash
#
# Syntax: build.sh -d [ROOT_DIRECTORY] -m [ debug | release ] [-c]
# Options:
#   -d Specify the project's root directory. Use './' if you're already in the project's root.
#   -m Specify build mode. Accepted values are 'debug' and 'release'
#   -c (Optional) Clean built files.  Use in conjunction with '-m'
#

while getopts d:m:hc flag; do
  case "$flag" in
  d) directory=${OPTARG} ;;
  m) mode=${OPTARG} ;;
  h)
    echo "Syntax: build.sh -d [ROOT_DIRECTORY] -m [ debug | release ]"
    echo "Options:"
    echo "  -d Specify the project's root directory. Use './' if you're already in the project's root."
    echo "  -m Specify build mode. Accepted values are 'debug' and 'release'"
    echo "  -c (Optional) Clean built files. Use in conjunction with '-m'"
    exit 0
    ;;
  c) clean=1 ;;
  *)
    echo "Invalid flag '$flag'"
    exit 1
    ;;
  esac
done

if [ "" = "${directory}" ]; then
  echo "Error: No directory provided. Try 'build.sh -h' for more information."
  exit 1
fi

if [ "" = "${mode}" ]; then
  echo "Error: No build mode specified. Try 'build.sh -h' for more information."
  exit 1
fi

if [ ! -d "${directory}" ]; then
  echo "Error: '${directory}' doesn't exist or isn't a directory."
  exit 1
fi

case "$mode" in
"debug")
  if [ "${clean}" -eq 1 ]; then
    echo "[ Clean | Debug ]"
    echo "cmake --build ./cmake-build-debug --target clean -j 9"
    cmake --build ./cmake-build-debug --target dsvcol -j 9
    echo "[ Clean finished ]"
  else
    echo "[ Build | Debug ]"
    echo "cmake --build ./cmake-build-debug --target dsvcol -j 9"
    cmake --build ./cmake-build-debug --target dsvcol -j 9
    echo "[ Build finished ]"
  fi
  ;;
"release")
  if [ "${clean}" -eq 1 ]; then
    echo "[ Clean | Release ]"
    echo "cmake --build ./cmake-build-release --target clean -j 9"
    cmake --build ./cmake-build-release --target dsvcol -j 9
    echo "[ Clean finished ]"
  else
    echo "[ Build | Release ]"
    echo "cmake --build ./cmake-build-release --target dsvcol -j 9"
    cmake --build ./cmake-build-release --target dsvcol -j 9
    echo "[ Build finished ]"
  fi
  ;;
*)
  echo "Invalid build mode '$mode'"
  exit 1
  ;;
esac
