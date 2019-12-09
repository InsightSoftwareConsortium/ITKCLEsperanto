#!/usr/bin/env bash

if test ! -d ./ITK; then
  git clone https://github.com/InsightSoftwareConsortium/ITK
  pushd ./ITK
  git checkout v5.1rc01
  popd
fi

gpu_module_dirs=(GPUCommon GPUFiniteDifference GPUAnisotropicSmoothing GPUImageFilterBase GPUSmoothing)

for module in ${gpu_module_dirs[@]}; do
  find ./ITKPythonPackage -name "*${module}*" -exec rm -rf "{}" +
  find ./ITKPythonPackage -name ITKConfig.cmake -exec sed -e 's/[;]ITKGPU[a-zA-Z]*//g' -i "{}" \;
done

python -m pip install cookiecutter
