#!/usr/bin/env bash

set -exE

if test $# -lt 4; then
  echo "Usage: ${0##*/} <ModulePath> <PackageName> <Description> <ExtraDependencies>"
  exit 1
fi

repo_dir="$( cd "$(dirname "${BASH_SOURCE[0]}")/.." ; pwd -P )"

mkdir -p $repo_dir/dist

pushd "$1"

rm -rf SetupPy
python -m cookiecutter \
  --no-input \
  $repo_dir/wrapping/ITKRepositoryPackageSetupCookieCutter \
  python_package_name="$2" \
  project_short_description="$3" \
  extra_package_dependencies="$4"
mv SetupPy/setup.py .

popd

./wrapping/dockcross-manylinux-build-module-wheels-opencl.sh $1
