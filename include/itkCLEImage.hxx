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

#ifndef itkCLEImage_hxx
#define itkCLEImage_hxx

#include "itkCLEImageDataManager.h"

namespace itk
{
template <typename TPixel, unsigned int VImageDimension>
CLEImage<TPixel, VImageDimension>::CLEImage()
{
  this->m_DataManager = ImageDataManager::New();
  this->m_DataManager->SetTimeStamp(this->GetTimeStamp());
  this->m_DataManager->SetImagePointer(this);
}

template <typename TPixel, unsigned int VImageDimension>
CLEImage<TPixel, VImageDimension>::~CLEImage() = default;

template <typename TPixel, unsigned int VImageDimension>
void
CLEImage<TPixel, VImageDimension>::Allocate(bool initialize)
{
  // allocate CPU memory - calling Allocate() in superclass
  Superclass::Allocate(initialize);

  this->ComputeOffsetTable();
  this->m_DataManager->Allocate();

  /* prevent unnecessary copy from CPU to GPU at the beginning */
  this->m_DataManager->SetTimeStamp(this->GetTimeStamp());
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEImage<TPixel, VImageDimension>::AllocateGPU(bool initialize)
{
  this->m_DataManager->AllocateGPU(initialize);

  /* prevent unnecessary copy from CPU to GPU at the beginning */
  this->m_DataManager->SetTimeStamp(this->GetTimeStamp());
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEImage<TPixel, VImageDimension>::Initialize()
{
  // CPU image initialize
  Superclass::Initialize();

  // CLE image initialize
  this->ComputeOffsetTable();
  this->m_DataManager->Initialize();

  /* prevent unnecessary copy from CPU to GPU at the beginning */
  this->m_DataManager->SetTimeStamp(this->GetTimeStamp());
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEImage<TPixel, VImageDimension>::Graft(const Self * data)
{
  auto * ptr = const_cast<ImageDataManager *>(data->GetDataManager());

  // call the superclass' implementation
  Superclass::Graft(ptr->GetImagePointer());

  // call GPU data graft function
  this->m_DataManager->SetImagePointer(this);
  this->m_DataManager->Graft(ptr);

  // Synchronize timestamp of GPUImage and GPUDataManager
  this->m_DataManager->SetTimeStamp(this->GetTimeStamp());
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEImage<TPixel, VImageDimension>::Graft(const DataObject * data)
{
  const Self * ptr = dynamic_cast<const Self *>(data);
  if (ptr)
  {
    this->Graft(ptr);
  }
  else
  {
    // pointer could not be cast back down
    itkExceptionMacro(<< "itk::CLEImage::Graft() cannot cast " << typeid(data).name() << " to "
                      << typeid(const Self *).name());
  }
}

template <typename TPixel, unsigned int VImageDimension>
void
CLEImage<TPixel, VImageDimension>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  this->m_DataManager->PrintSelf(os, indent);
}

} // namespace itk

#endif
