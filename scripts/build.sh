#!/bin/bash

SCRIPTS_DIR=$(cd $(dirname $0); pwd)
TOP_DIR=${SCRIPTS_DIR}/..
BUILD_DIR=${TOP_DIR}/build_root


function install_dependencies() {
  sudo -S apt -y install build-essential cmake qtbase5-dev libboost-all-dev ragel
}


function build_klogg() {
  mkdir -p ${BUILD_DIR}
  pushd ${BUILD_DIR}
  local version_id=$(cat /etc/os-release | grep VERSION_ID | awk -F= '{print $2}')
  echo "build on ${version_id}"
  if [ $version_id == "18.04" ];then
    echo "ubuntu 18.04, disable LTO"
    cmake -DCPM_SOURCE_CACHE=../cpm_cache -DKLOGG_GENERIC_CPU=ON -DKLOGG_USE_LTO=OFF ..
  else
    cmake -DCPM_SOURCE_CACHE=../cpm_cache ..
  fi
  
  cmake --build . -j 8
  popd
}

function extract_from_tar() {
  pushd ${TOP_DIR}
  tar xvf cpm_cache.tar.gz
  popd
}

function build_deb_package() {
  echo "build deb now"
  pushd ${BUILD_DIR}
  cpack
  popd
}

install_dependencies
extract_from_tar
build_klogg
build_deb_package
