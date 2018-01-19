#!/bin/bash
if [ $# -lt 3 ] ; then
  echo "Usage: $0 <vlc_path> <project_path>"
  exit 1
fi
LIBVLC_LIBRARY=$1
LIBVLCCORE_LIBRARY=$2
PROJECT_PATH=$3
PROJECT_NAME=$4
install_name_tool -change @loader_path/lib/libvlc.5.dylib $LIBVLC_LIBRARY $PROJECT_PATH/$PROJECT_NAME
install_name_tool -change @loader_path/lib/libvlccore.8.dylib $LIBVLCCORE_LIBRARY $PROJECT_PATH/$PROJECT_NAME