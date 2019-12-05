#!/usr/bin/env bash

if test ! -d ./ITK; then
  git clone https://github.com/InsightSoftwareConsortium/ITK
  pushd ./ITK
  git checkout 5886942fa903409d11411303e30aa9579a3ebec5
  popd
fi

gpu_module_dirs=(GPUCommon GPUFiniteDifference GPUAnisotropicSmoothing GPUImageFilterBase GPUSmoothing)

for module in ${gpu_module_dirs[@]}; do
  find ./ITKPythonPackage -name "*${module}*" -exec rm -rf "{}" +
  find ./ITKPythonPackage -name ITKConfig.cmake -exec sed -e 's/[;]ITKGPU[a-zA-Z]*//g' -i "{}" \;
done

python -m pip install cookiecutter
