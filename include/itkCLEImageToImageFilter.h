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
#ifndef itkCLEImageToImageFilter_h
#define itkCLEImageToImageFilter_h

#include "itkCLEImage.h"
#include "itkImageToImageFilter.h"

namespace itk
{
/** \class CLEAddImageFilter
 *
 * \brief class to abstract the behaviour of the CLE filters.
 *
 * CLEImageToImageFilter is the CLE version of ImageToImageFilter.
 * This class can accept both CPU and GPU image as input and output,
 * and apply filter accordingly. If GPU is available for use, then
 * CLEGenerateData() is called. Otherwise, GenerateData() in the
 * parent class (i.e., ImageToImageFilter) will be called.
 *
 * \ingroup CLEsperanto
 */
template <typename TInputImage,
          typename TOutputImage,
          typename TParentImageFilter = ImageToImageFilter<TInputImage, TOutputImage>>
class ITK_TEMPLATE_EXPORT CLEImageToImageFilter : public TParentImageFilter
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(CLEImageToImageFilter);

  /** Standard class type aliases. */
  using Self = CLEImageToImageFilter;
  using Superclass = TParentImageFilter;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(CLEImageToImageFilter, TParentImageFilter);

  /** Superclass type alias. */
  using typename Superclass::DataObjectIdentifierType;
  using typename Superclass::OutputImageRegionType;
  using typename Superclass::OutputImagePixelType;

  /** Some convenient type alias. */
  using InputImageType = TInputImage;
  using InputImagePointer = typename InputImageType::Pointer;
  using InputImageConstPointer = typename InputImageType::ConstPointer;
  using InputImageRegionType = typename InputImageType::RegionType;
  using InputImagePixelType = typename InputImageType::PixelType;

  /** ImageDimension constants */
  static constexpr unsigned int InputImageDimension = TInputImage::ImageDimension;
  static constexpr unsigned int OutputImageDimension = TOutputImage::ImageDimension;

  // macro to set if CLE is used
  itkSetMacro(CLEEnabled, bool);
  itkGetConstMacro(CLEEnabled, bool);
  itkBooleanMacro(CLEEnabled);

  void
  GenerateData() override;
  virtual void
  GraftOutput(typename itk::CLETraits<TOutputImage>::Type * output);
  virtual void
  GraftOutput(const DataObjectIdentifierType & key, typename itk::CLETraits<TOutputImage>::Type * output);

protected:
  void
  GraftOutput(DataObject * output) override;
  void
  GraftOutput(const DataObjectIdentifierType & key, DataObject * output) override;
  CLEImageToImageFilter();
  ~CLEImageToImageFilter() override;

  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  virtual void
  CLEGenerateData()
  {}

private:
  bool m_CLEEnabled{ true };
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkCLEImageToImageFilter.hxx"
#endif

#endif
