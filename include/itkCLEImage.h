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

#ifndef itkCLEImage_h
#define itkCLEImage_h

#include "itkImage.h"
#include "itkVersion.h"
#include "itkObjectFactoryBase.h"

namespace itk
{
  template <typename TPixel, unsigned int VDimension>
  class CLEDataManager;
  template <typename TPixel, unsigned int VDimension>
  class CLEImageDataManager;

/** \class CLEImage
 *  \brief Templated n-dimensional image class for CLEsperanto.
 *
 * Derived from itk Image class to use with CLEsperanto image filters.
 * This class manages both CPU and GPU memory implicitly, and
 * can be used with non-GPU itk filters as well. Memory transfer
 * between CPU and GPU is done automatically and implicitly.
 *
 * \ingroup CLEsperanto
 */
template <typename TPixel, unsigned int VImageDimension = 2>
class ITK_TEMPLATE_EXPORT CLEImage : public Image<TPixel, VImageDimension>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(CLEImage);

  using Self = CLEImage<TPixel, VImageDimension>;
  using Superclass = Image<TPixel, VImageDimension>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;
  using ConstWeakPointer = WeakPointer<const Self>;

  using typename itk::Image<TPixel, VImageDimension>::IndexType;
  using typename itk::Image<TPixel, VImageDimension>::PixelContainer;
  using typename itk::Image<TPixel, VImageDimension>::AccessorType;

  using DataManager = CLEDataManager<TPixel, VImageDimension>;
  using ImageDataManager = CLEImageDataManager<TPixel, VImageDimension>;

  itkNewMacro(Self);

  itkTypeMacro(CLEImage, Image);

  itkGetModifiableObjectMacro(DataManager, ImageDataManager);
  DataManager*
  GetGPUDataManager()
  {
    return this->m_DataManager.GetPointer();
  }

  static constexpr unsigned int ImageDimension = VImageDimension;

  //
  // Allocate CPU and GPU memory space
  //
  void
  Allocate(bool initialize = false) override;

  void
  Initialize() override;

  void
  UpdateBuffers()
  {
    this->m_DataManager->Update();
  }

  void
  FillBuffer(const TPixel & value)
  {
    this->m_DataManager->SetGPUDirtyFlag(true);
    Superclass::FillBuffer(value);
  }

  void
  SetPixel(const IndexType & index, const TPixel & value)
  {
    m_DataManager->SetGPUDirtyFlag(true);
    Superclass::SetPixel(index, value);
  }

  const TPixel &
  GetPixel(const IndexType & index) const
  {
    return Superclass::GetPixel(index);
  }

  TPixel &
  GetPixel(const IndexType & index)
  {
    this->m_DataManager->SetGPUDirtyFlag(true);
    return Superclass::GetPixel(index);
  }

  const TPixel & operator[](const IndexType & index) const
  {
    return Superclass::operator[](index);
  }

  TPixel & operator[](const IndexType & index)
  {
    return Superclass::operator[](index);
  }

  TPixel *
  GetBufferPointer() override
  {
    this->m_DataManager->SetGPUDirtyFlag(true);
    return Superclass::GetBufferPointer();
  }

  const TPixel *
  GetBufferPointer() const override
  {
    return Superclass::GetBufferPointer();
  }

  PixelContainer *
  GetPixelContainer()
  {
    this->m_DataManager->SetGPUDirtyFlag(true);
    return Superclass::GetPixelContainer();
  }

  const PixelContainer *
  GetPixelContainer() const
  {
    return Superclass::GetPixelContainer();
  }

  void
  SetPixelContainer(PixelContainer* container)
  {
    this->m_DataManager->SetGPUDirtyFlag(true);
    Superclass::SetPixelContainer(container);
  }

  /** Graft the data and information from one CLEImage to another. */
  virtual void
  Graft(const Self* data);

  /** Return the Pixel Accessor object */
  AccessorType
  GetPixelAccessor()
  {
    this->m_DataManager->SetGPUBufferDirty();
    return Superclass::GetPixelAccessor();
  }

  /** Return the Pixel Accesor object */
  const AccessorType
  GetPixelAccessor() const
  {
    return Superclass::GetPixelAccessor();
  }

  using NeighborhoodAccessorFunctorType = NeighborhoodAccessorFunctor<Self>;

  NeighborhoodAccessorFunctorType
  GetNeighborhoodAccessor()
  {
    this->m_DataManager->SetGPUBufferDirty();
    return NeighborhoodAccessorFunctorType();
  }

  const NeighborhoodAccessorFunctorType
  GetNeighborhoodAccessor() const
  {
    return NeighborhoodAccessorFunctorType();
  }

  /* Override DataHasBeenGenerated() in DataObject class.
   * We need this because CPU time stamp is always bigger
   * than GPU's. That is because Modified() is called at
   * the end of each filter in the pipeline so although we
   * increment GPU's time stamp in GPUGenerateData() the
   * CPU's time stamp will be increased after that.
   */
  void
  DataHasBeenGenerated() override
  {
    Superclass::DataHasBeenGenerated();
    //if (m_DataManager->IsCPUBufferDirty())
    {
      this->m_DataManager->Modified();
    }
  }

protected:
  CLEImage();
  void
  PrintSelf(std::ostream& os, Indent indent) const override;
  void
  Graft(const DataObject * data) override;

  ~CLEImage() override;

  using Superclass::Graft;

private:
  typename CLEImageDataManager<TPixel,VImageDimension>::Pointer m_DataManager;
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkCLEImage.hxx"
#endif

#endif
