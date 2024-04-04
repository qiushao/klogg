#!/bin/bash

SCRIPTS_DIR=$(cd $(dirname $0); pwd)
TOP_DIR=${SCRIPTS_DIR}/..
BUILD_DIR=${TOP_DIR}/build_root
DEB_DIR=${BUILD_DIR}/packages

# actually we get the first matched deb path
get_deb_path() {
  deb_paths=($(find ${DEB_DIR} -name klogg*.deb -exec realpath {} \;))
  length=${#deb_paths[@]}
  
  if [[ ${length} -lt 1 ]]; then
    echo "klogg deb not found!"
    exit 1
  fi

  first_deb_path=${deb_paths[0]}
  echo "${first_deb_path}"
}

install_deb() {
  deb_path=$(get_deb_path)
  echo "${deb_path}"
  sudo dpkg -i ${deb_path}
}

install_deb