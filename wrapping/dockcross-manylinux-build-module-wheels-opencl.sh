#!/bin/bash

# Run this script to build the Python wheel packages for Linux for an ITK
# external module.
#
# Versions can be restricted by passing them in as arguments to the script
# For example,
#
#   scripts/dockcross-manylinux-build-module-wheels.sh #   <module-relative-directory> cp27mu cp35

set -x

# Pull dockcross manylinux images
docker pull dockcross/manylinux-x64

# Generate dockcross scripts
docker run dockcross/manylinux-x64 > /tmp/dockcross-manylinux-x64
chmod u+x /tmp/dockcross-manylinux-x64

script_dir=$(cd $(dirname $0) || exit 1; pwd)

if test $# -lt 1; then
  workdir="."
else
  workdir="$1"
  shift
fi

if ! test -d ./OpenCL-ICD-Loader; then
  git clone https://github.com/KhronosGroup/OpenCL-ICD-Loader
  pushd OpenCL-ICD-Loader
  git checkout 978b4b3a29a3aebc86ce9315d5c5963e88722d03
  popd
  pushd OpenCL-ICD-Loader/inc
  git clone https://github.com/KhronosGroup/OpenCL-Headers
  pushd OpenCL-Headers
  git checkout c5a4bbeabb10d8ed3d1c651b93aa31737bc473dd
  popd
  cp -r OpenCL-Headers/CL ./
  popd
  mkdir OpenCL-ICD-Loader-build
  /tmp/dockcross-manylinux-x64 cmake -BOpenCL-ICD-Loader-build -HOpenCL-ICD-Loader -GNinja
  /tmp/dockcross-manylinux-x64 ninja -COpenCL-ICD-Loader-build
fi

# Build wheels
mkdir -p dist
DOCKER_ARGS="-e ELASTIX_USE_OPENCL=1 -v $(pwd)/dist:/work/dist/ -v $(pwd)/ITKPythonPackage:/ITKPythonPackage -v $(pwd)/tools:/tools -v $(pwd)/OpenCL-ICD-Loader/inc/CL:/usr/include/CL -v $(pwd)/OpenCL-ICD-Loader-build/libOpenCL.so.1.2:/usr/lib64/libOpenCL.so.1 -v $(pwd)/OpenCL-ICD-Loader-build/libOpenCL.so.1.2:/usr/lib64/libOpenCL.so --workdir /work/${workdir}"
/tmp/dockcross-manylinux-x64 \
  -a "$DOCKER_ARGS" \
  "/ITKPythonPackage/scripts/internal/manylinux-build-module-wheels.sh" "$@"
