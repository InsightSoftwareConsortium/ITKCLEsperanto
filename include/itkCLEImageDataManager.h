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

#ifndef itkCLEImageDataManager_h
#define itkCLEImageDataManager_h

#include "itkObject.h"
#include "itkTimeStamp.h"
#include "itkLightObject.h"
#include "itkObjectFactory.h"

#include "itkCLEDataManager.h"

namespace itk
{
template <typename TPixel, unsigned int VDimension>
class CLEImage;
/**
 * \class CLEImageDataManager
 *
 * DataManager for CLEImage. This class will take care of data synchronization
 * between CPU Image and GPU Image using CLEsperanto
 *
 * \ingroup CLEsperanto
 */
template <typename TPixel, unsigned int VImageDimension>
class ITK_TEMPLATE_EXPORT CLEImageDataManager : public CLEDataManager<TPixel, VImageDimension>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(CLEImageDataManager);

  using Self = CLEImageDataManager<TPixel, VImageDimension>;
  using Superclass = CLEDataManager<TPixel, VImageDimension>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  itkNewMacro(Self);

  static constexpr unsigned int ImageDimension = VImageDimension;

  virtual void
  Allocate();

  virtual void
  Initialize();

  void
  SetImagePointer(CLEImage<TPixel, VImageDimension> * img)
  {
    this->m_Image = img;
  }

  CLEImage<TPixel, VImageDimension> *
  GetImagePointer()
  {
    return this->m_Image.GetPointer();
  }

protected:
  CLEImageDataManager() = default;
  ~CLEImageDataManager() override = default;

  /** actual GPU->CPU memory copy takes place here */
  virtual void
  UpdateCPUBuffer() override;

  /** actual CPU->GPU memory copy takes place here */
  virtual void
  UpdateGPUBuffer() override;

  WeakPointer<CLEImage<TPixel, VImageDimension>> m_Image; // WeakPointer has to be used here
                                                          // to avoid SmartPointer loop
};

} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkCLEImageDataManager.hxx"
#endif

#endif
