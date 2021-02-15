#!/bin/bash

# exit when any command fails
set -e

# check for commandline args
if [ "$#" -ne 1 ]
then
  echo "Usage: release.sh <release-name>"
  exit 1
fi

# read release name
releasedir="arduinoide/releases/$1"

# create release dir
mkdir -p $releasedir

# src dir
srcdir="$releasedir/Drehdings/"

# create isrc dir
mkdir -p $srcdir

# copy files
find platformio/drehding/ -name \*.h -exec cp {} $srcdir/ \;
find platformio/drehding/ -name \*.cpp -exec cp {} $srcdir/ \;

# rename
mv "${srcdir}/main.cpp" "${srcdir}/Drehdings.ino"

exit 0
