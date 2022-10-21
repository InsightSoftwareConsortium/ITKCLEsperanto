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

#ifndef itkCLEDataManager_hxx
#define itkCLEDataManager_hxx

#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"

//#define VERBOSE

namespace itk
{

template <typename TPixel, unsigned int VImageDimension>
CLEDataManager<TPixel, VImageDimension>::CLEDataManager()
{
  this->Initialize();
}

template <typename TPixel, unsigned int VImageDimension>
CLEDataManager<TPixel, VImageDimension>::~CLEDataManager()
{}

template <typename TPixel, unsigned int VImageDimension>
void
CLEDataManager<TPixel, VImageDimension>::Allocate(bool)
{}

template <typename TPixel, unsigned int VImageDimension>
void
CLEDataManager<TPixel, VImageDimension>::AllocateGPU(bool)
{}

template <typename TPixel, unsigned int VImageDimension>
void
CLEDataManager<TPixel, VImageDimension>::Initialize()
{
  this->m_IsGPUBufferDirty = false;
  this->m_IsCPUBufferDirty = false;
  this->m_BufferShape = { 0, 0, 0 };
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEDataManager<TPixel, VImageDimension>::Update()
{
  this->UpdateGPUBuffer();
  this->UpdateCPUBuffer();
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEDataManager<TPixel, VImageDimension>::UpdateCPUBuffer()
{
  this->m_IsCPUBufferDirty = false;
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEDataManager<TPixel, VImageDimension>::UpdateGPUBuffer()
{
  this->m_IsGPUBufferDirty = false;
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEDataManager<TPixel, VImageDimension>::Graft(const CLEDataManager * data)
{
  if (data)
  {
    this->m_BufferShape = data->m_BufferShape;
    this->m_GPUBuffer = data->m_GPUBuffer;
    this->m_IsCPUBufferDirty = data->m_IsCPUBufferDirty;
    this->m_IsGPUBufferDirty = data->m_IsGPUBufferDirty;
  }
}
template <typename TPixel, unsigned int VImageDimension>
void
CLEDataManager<TPixel, VImageDimension>::PrintSelf(std::ostream & os, Indent indent) const
{
  os << indent << "CLEDataManager (" << this << ")" << std::endl;
  os << indent << "m_BufferShape: (" << this->m_BufferShape[0] << ", " << this->m_BufferShape[1] << ", "
     << this->m_BufferShape[2] << ")" << std::endl;
  os << indent << "m_IsGPUBufferDirty: " << this->m_IsGPUBufferDirty << std::endl;
  os << indent << "m_IsCPUBufferDirty: " << this->m_IsCPUBufferDirty << std::endl;
  // os << indent << "m_GPUBuffer: " << this->m_GPUBuffer << std::endl;
}

} // namespace itk

#endif
