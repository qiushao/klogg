#!/bin/bash

SCRIPTS_DIR=$(cd $(dirname $0); pwd)
TOP_DIR=${SCRIPTS_DIR}/..
BUILD_DIR=${TOP_DIR}/build_root

read -s -p "Enter sudo Password: " sudo_passwd
echo # Move to a new line

install_dependencies() {
  echo $sudo_passwd| sudo -S apt -y install build-essential cmake qtbase5-dev libboost-all-dev ragel
}

build_klogg() {
  mkdir -p BUILD_DIR
  pushd ${BUILD_DIR}
  cmake -DCPM_SOURCE_CACHE=../cpm_cache ..
  cmake --build . -j
  popd
}

extract_from_tar() {
  pushd ${TOP_DIR}
  tar xvf cpm_cache.tar.gz
  popd
}

build_deb_package() {
  echo "build deb now"
  pushd ${BUILD_DIR}
  cpack
  popd
}

install_dependencies
extract_from_tar
build_klogg
build_deb_package