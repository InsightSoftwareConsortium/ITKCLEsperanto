/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkCLEAddImageFilter_hxx
#define itkCLEAddImageFilter_hxx

#include "clesperanto.hpp"

namespace itk
{
template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
CLEAddImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::CLEAddImageFilter() = default;

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
CLEAddImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::~CLEAddImageFilter() = default;

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEAddImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::CLEGenerateData()
{
  Input1ImagePointer image1 = this->GetInput(0);
  Input2ImagePointer image2 = this->GetInput(1);
  OutputImagePointer output = this->GetOutput();
  output->SetBufferedRegion(output->GetRequestedRegion());
  output->AllocateGPU();

  auto image1GPU = image1->GetGPUDataManager()->GetGPUBuffer();
  auto image2GPU = image2->GetGPUDataManager()->GetGPUBuffer();
  auto outputGPU = output->GetGPUDataManager()->GetGPUBuffer();

  CLEContextManager::GetInstance().AddImages(image1GPU, image2GPU, outputGPU);
  output->GetGPUDataManager()->SetCPUDirtyFlag(true);

  itkDebugMacro("I am adding images on the GPU\n");
}

} // end namespace itk

#endif
