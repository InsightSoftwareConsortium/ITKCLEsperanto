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
#ifndef itkCLEUnaryGeneratorImageFilter_h
#define itkCLEUnaryGeneratorImageFilter_h

#include "itkUnaryGeneratorImageFilter.h"
#include "itkCLEInPlaceImageFilter.h"

namespace itk
{
/** \class CLEUnaryGeneratorImageFilter
 * \brief Implements pixel-wise generic operation on one image using CLEsperanto.
 *
 * CLE version of unary image filter.
 *
 * \ingroup   CLEsperanto
 */
template <typename TInputImage,
          typename TOutputImage,
          typename TParentImageFilter = UnaryGeneratorImageFilter<TInputImage, TOutputImage>>
class ITK_TEMPLATE_EXPORT CLEUnaryGeneratorImageFilter
  : public CLEInPlaceImageFilter<TInputImage, TOutputImage, TParentImageFilter>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(CLEUnaryGeneratorImageFilter);

  /** Standard class type aliases. */
  using Self = CLEUnaryGeneratorImageFilter;
  using Superclass = CLEInPlaceImageFilter<TInputImage, TOutputImage>;
  using CPUSuperclass = TParentImageFilter;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(CLEUnaryGeneratorImageFilter, CLEInPlaceImageFilter);

  using InputImageType = TInputImage;
  using InputImagePointer = typename InputImageType::ConstPointer;
  using InputImageRegionType = typename InputImageType::RegionType;
  using InputImagePixelType = typename InputImageType::PixelType;

  using OutputImageType = TOutputImage;
  using OutputImagePointer = typename OutputImageType::Pointer;
  using OutputImageRegionType = typename OutputImageType::RegionType;
  using OutputImagePixelType = typename OutputImageType::PixelType;

protected:
  CLEUnaryGeneratorImageFilter() = default;
  ~CLEUnaryGeneratorImageFilter() override = default;

  void
  GenerateOutputInformation() override;

  void
  CLEGenerateData() override;
};

} // end of namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkCLEUnaryGeneratorImageFilter.hxx"
#endif

#endif
