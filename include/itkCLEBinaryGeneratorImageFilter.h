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
#ifndef itkCLEBinaryGeneratorImageFilter_h
#define itkCLEBinaryGeneratorImageFilter_h

#include "itkBinaryGeneratorImageFilter.h"
#include "itkCLEInPlaceImageFilter.h"
#include "itkSimpleDataObjectDecorator.h"

namespace itk
{
/** \class CLEBinaryGeneratorImageFilter
 * \brief Implements operation on two images using CLEsperanto.
 *
 * CLE version of binary generator image filter.
 *
 * \ingroup   CLEsperanto
 */
template <typename TInputImage1,
          typename TInputImage2,
          typename TOutputImage,
          typename TParentImageFilter = BinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage>>
class ITK_TEMPLATE_EXPORT CLEBinaryGeneratorImageFilter : public CLEInPlaceImageFilter<TInputImage1, TOutputImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(CLEBinaryGeneratorImageFilter);

  /** Standard class type aliases. */
  using Self = CLEBinaryGeneratorImageFilter;
  using Superclass = CLEInPlaceImageFilter<TInputImage1, TOutputImage>;
  using CPUSuperclass = TParentImageFilter;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(CLEBinaryGeneratorImageFilter, CLEInPlaceImageFilter);

  using Input1ImageType = TInputImage1;
  using Input1ImagePointer = typename InputImageType::ConstPointer;
  using Input1ImageRegionType = typename InputImageType::RegionType;
  using Input1ImagePixelType = typename InputImageType::PixelType;
  using DecoratedInput1ImagePixelType = SimpleDataObjectDecorator<Input1ImagePixelType>;

  using Input2ImageType = TInputImage2;
  using Input2ImagePointer = typename InputImageType::ConstPointer;
  using Input2ImageRegionType = typename InputImageType::RegionType;
  using Input2ImagePixelType = typename InputImageType::PixelType;
  using DecoratedInput2ImagePixelType = SimpleDataObjectDecorator<Input2ImagePixelType>;

  using OutputImageType = TOutputImage;
  using OutputImagePointer = typename OutputImageType::Pointer;
  using OutputImageRegionType = typename OutputImageType::RegionType;
  using OutputImagePixelType = typename OutputImageType::PixelType;

  /** Connect the first operand for pixel-wise operation. */
  virtual void
  SetInput1(const TInputImage1 * image1);
  virtual void
  SetInput1(const DecoratedInput1ImagePixelType * input1);
  virtual void
  SetInput1(const Input1ImagePixelType & input1);

  /** Set the first operand as a constant. */
  virtual void
  SetConstant1(const Input1ImagePixelType & input1);

  /** Get the constant value of the first operand. An exception is thrown if
   * the first operand is not a constant. */
  virtual const Input1ImagePixelType &
  GetConstant1() const;

  /** Connect the second operand for pixel-wise operation. */
  virtual void
  SetInput2(const TInputImage2 * image2);
  virtual void
  SetInput2(const DecoratedInput2ImagePixelType * input2);
  virtual void
  SetInput2(const Input2ImagePixelType & input2);


  /** Set the second operand as a constant. */
  virtual void
  SetConstant2(const Input2ImagePixelType & input2);
  void
  SetConstant(Input2ImagePixelType ct)
  {
    this->SetConstant2(ct);
  }
  const Input2ImagePixelType &
  GetConstant() const
  {
    return this->GetConstant2();
  }

  /** Get the constant value of the second operand. An exception is thrown if
   * the second operand is not a constant. */
  virtual const Input2ImagePixelType &
  GetConstant2() const;

   /** ImageDimension constants */
  static constexpr unsigned int InputImage1Dimension = TInputImage1::ImageDimension;
  static constexpr unsigned int InputImage2Dimension = TInputImage2::ImageDimension;
  static constexpr unsigned int OutputImageDimension = TOutputImage::ImageDimension;

#ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro(SameDimensionCheck1,
                  (Concept::SameDimension<Self::InputImage1Dimension, Self::InputImage2Dimension>));
  itkConceptMacro(SameDimensionCheck2,
                  (Concept::SameDimension<Self::InputImage1Dimension, Self::OutputImageDimension>));
  // End concept checking
#endif

protected:
  CLEBinaryGeneratorImageFilter();
  ~CLEBinaryGeneratorImageFilter() override = default;

  void
  GenerateOutputInformation() override;

};

} // end of namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkCLEBinaryGeneratorImageFilter.hxx"
#endif

#endif
