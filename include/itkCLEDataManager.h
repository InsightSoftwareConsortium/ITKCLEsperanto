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

#ifndef itkCLEDataManager_h
#define itkCLEDataManager_h

#include "itkObject.h"
#include "itkDataObject.h"
#include "itkObjectFactory.h"

#include "clesperanto.hpp"

namespace itk
{
/** \class CLEDataManager
 * \brief CLE memory manager implemented using OpenCL. Required by CLEImage class.
 *
 * This class serves as a base class for CLEsperanto data container for CLEImage class,
 * which is similar to ImageBase class for Image class. However, all the image-related
 * meta data will be already stored in image class (parent of CLEImage), therefore
 * we did not name it CLEImageBase. Rather, this class is a CLE-specific data manager
 * that provides functionalities for CPU-GPU data synchronization and grafting GPU data.
 *
 * \ingroup CLEsperanto
 */
template <typename TPixel, unsigned int VImageDimension>
class CLEDataManager : public Object // DataObject//
{
  template<typename,unsigned int> friend class CLEImage;

public:
  ITK_DISALLOW_COPY_AND_MOVE(CLEDataManager);

  using Self = CLEDataManager<TPixel, VImageDimension>;
  using Superclass = Object;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  itkNewMacro(Self);
  itkTypeMacro(CLEDataManager, Object);

  static constexpr unsigned int ImageDimension = VImageDimension;

  virtual void
  Allocate();

  virtual void
  Initialize();

  void
  SetCPUDirtyFlag(bool isDirty)
  {
    this->m_IsCPUBufferDirty = isDirty;
  }
  
  void
  SetGPUDirtyFlag(bool isDirty)
  {
    this->m_IsGPUBufferDirty = isDirty;
  }
  
  bool
  IsCPUBufferDirty() const
  {
    return this->m_IsCPUBufferDirty;
  }
  
  bool
  IsGPUBufferDirty() const
  {
    return this->m_IsGPUBufferDirty;
  }

  /** Synchronize CPU and GPU buffers (using dirty flags) */
  void
  Update();

  /** Method for grafting the content of one CLEDataManager into another one */
  virtual void
  Graft(const CLEDataManager * data);

protected:
  CLEDataManager();
  ~CLEDataManager() override;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  /** actual GPU->CPU memory copy takes place here */
  virtual void
  UpdateCPUBuffer();

  /** actual CPU->GPU memory copy takes place here */
  virtual void
  UpdateGPUBuffer();

  std::array<size_t, 3> m_BufferShape;
  cle::Object m_GPUBuffer;

  /** checks if buffer needs to be updated */
  bool m_IsGPUBufferDirty;
  bool m_IsCPUBufferDirty;
};

} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkCLEDataManager.hxx"
#endif

#endif
