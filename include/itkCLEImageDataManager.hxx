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

#ifndef itkCLEImageDataManager_hxx
#define itkCLEImageDataManager_hxx

#include "itkCLEContextManager.h"
#include "itkCLEImage.h"

namespace itk
{

template <typename TPixel, unsigned int VImageDimension>
void
CLEImageDataManager<TPixel, VImageDimension>::Allocate(bool initialize)
{
  auto size = this->m_Image->GetBufferedRegion().GetSize();
  this->m_BufferShape = { size[0], size[1], VImageDimension == 3 ? 3 : 1 };
  Superclass::Allocate(initialize);
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEImageDataManager<TPixel, VImageDimension>::AllocateGPU(bool initialize)
{
  auto size = this->m_Image->GetBufferedRegion().GetSize();
  this->m_BufferShape = { size[0], size[1], VImageDimension == 3 ? 3 : 1 };
  if (!initialize)
    this->m_GPUBuffer = CLEContextManager::GetInstance().Create<TPixel>(this->m_BufferShape);
  else
  {
    std::vector<TPixel> buffer(this->m_BufferShape[0] *
                               this->m_BufferShape[1] *
                               this->m_BufferShape[2]);
    std::fill(buffer.begin(), buffer.end(), 0);
    this->m_GPUBuffer = CLEContextManager::GetInstance().Push<TPixel>(buffer, this->m_BufferShape);
  }
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEImageDataManager<TPixel, VImageDimension>::Initialize()
{
  if (m_Image.IsNotNull())
  {
    auto size = this->m_Image->GetBufferedRegion().GetSize();
    this->m_BufferShape = { size[0], size[1], VImageDimension == 3 ? 3 : 1 };
  }
  Superclass::Initialize();
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEImageDataManager<TPixel, VImageDimension>::UpdateCPUBuffer()
{
  if (this->m_IsCPUBufferDirty)
  {
    Allocate();
    std::vector<TPixel> buffer = CLEContextManager::GetInstance().Pull<TPixel>(this->m_GPUBuffer);
    size_t              i = 0;
    itk::ImageRegionIterator<CLEImage<TPixel, VImageDimension>> itr(this->m_Image, this->m_Image->GetBufferedRegion());
    itr.GoToBegin();
    while (!itr.IsAtEnd())
    {
      itr.Set(buffer[i++]);
      ++itr;
    }
    itkDebugMacro("I am pulling from the GPU\n");
  }
  Superclass::UpdateCPUBuffer();
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEImageDataManager<TPixel, VImageDimension>::UpdateGPUBuffer()
{
  if (this->m_IsGPUBufferDirty)
  {
    // Transfer itk::Image into our STL Buffer
    std::vector<TPixel>                                              buffer;
    itk::ImageRegionConstIterator<CLEImage<TPixel, VImageDimension>> itr(this->m_Image,
                                                                         this->m_Image->GetBufferedRegion());
    itr.GoToBegin();
    while (!itr.IsAtEnd())
    {
      buffer.push_back(itr.Get());
      ++itr;
    }
    this->m_GPUBuffer = CLEContextManager::GetInstance().Push<TPixel>(buffer, this->m_BufferShape);
    itkDebugMacro("I am pushing to the GPU\n");
  }
  Superclass::UpdateGPUBuffer();
}

} // namespace itk

#endif
