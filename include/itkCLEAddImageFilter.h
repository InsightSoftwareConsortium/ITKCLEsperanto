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
#ifndef itkCLEAddImageFilter_h
#define itkCLEAddImageFilter_h

#include "itkAddImageFilter.h"
#include "itkCLEBinaryGeneratorImageFilter.h"

namespace itk
{
/** \class CLEAddImageFilter
 * \brief Pixel-wise addition of two images using CLEsperanto hardware acceleration
 *
 * This class is replicates the functionality provided in AddImgeFilter using CLEsperanto
 * 
 * \see AddImageFilter.
 *
 * \ingroup CLEsperanto
 */
template <typename TInputImage1,
          typename TInputImage2 = TInputImage1,
          typename TOutputImage = TInputImage1,
          typename TParentImageFilter = AddImageFilter<TInputImage1, TInputImage2, TOutputImage>>
class ITK_TEMPLATE_EXPORT CLEAddImageFilter
  : public CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(CLEAddImageFilter);

  /** Standard class type aliases. */
  using Self = CLEAddImageFilter;
  using Superclass = CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage>;
  using CPUSuperclass = TParentImageFilter;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(CLEAddImageFilter, CLEImageToImageFilter);

#ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro(Input1Input2OutputAdditiveOperatorsCheck,
                  (Concept::AdditiveOperators<typename TInputImage1::PixelType,
                                              typename TInputImage2::PixelType,
                                              typename TOutputImage::PixelType>));
  // End concept checking
#endif

protected:
  CLEAddImageFilter();
  ~CLEAddImageFilter() override;

  void
  CLEGenerateData() override;
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkCLEAddImageFilter.hxx"
#endif

#endif
