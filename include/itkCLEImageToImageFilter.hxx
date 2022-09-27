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
#ifndef itkCLEImageToImageFilter_hxx
#define itkCLEImageToImageFilter_hxx


namespace itk
{

template <typename TInputImage, typename TOutputImage, typename TParentImageFilter>
CLEImageToImageFilter<TInputImage, TOutputImage, TParentImageFilter>::CLEImageToImageFilter()
{}

template <typename TInputImage, typename TOutputImage, typename TParentImageFilter>
CLEImageToImageFilter<TInputImage, TOutputImage, TParentImageFilter>::~CLEImageToImageFilter() = default;

template <typename TInputImage, typename TOutputImage, typename TParentImageFilter>
void
CLEImageToImageFilter<TInputImage, TOutputImage, TParentImageFilter>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "CLE: " << (m_CLEEnabled ? "Enabled" : "Disabled") << std::endl;
}

template <typename TInputImage, typename TOutputImage, typename TParentImageFilter>
void
CLEImageToImageFilter<TInputImage, TOutputImage, TParentImageFilter>::GenerateData()
{
  if (!m_CLEEnabled) // call CPU update function
  {
    Superclass::GenerateData();
  }
  else // call CLE update function
  {
    // Call a method to allocate memory for the filter's outputs
    this->AllocateOutputs();

    CLEGenerateData();
  }
}

template <typename TInputImage, typename TOutputImage, typename TParentImageFilter>
void
CLEImageToImageFilter<TInputImage, TOutputImage, TParentImageFilter>::GraftOutput(
  typename itk::CLETraits<TOutputImage>::Type * output)
{
  using CLEOutputImage = typename itk::CLETraits<TOutputImage>::Type;
  typename CLEOutputImage::Pointer cleImage = dynamic_cast<CLEOutputImage *>(this->GetOutput());

  cleImage->Graft(output);
}

template <typename TInputImage, typename TOutputImage, typename TParentImageFilter>
void
CLEImageToImageFilter<TInputImage, TOutputImage, TParentImageFilter>::GraftOutput(DataObject * output)
{
  using CLEOutputImage = typename itk::CLETraits<TOutputImage>::Type;
  auto * cleImage = dynamic_cast<CLEOutputImage *>(output);
  if (cleImage)
  {
    this->GraftOutput(cleImage);
  }
  else
  {
    itkExceptionMacro(<< "itk::CLEImageToImageFilter::GraftOutput() cannot cast " << typeid(output).name() << " to "
                      << typeid(CLEOutputImage *).name());
  }
}

template <typename TInputImage, typename TOutputImage, typename TParentImageFilter>
void
CLEImageToImageFilter<TInputImage, TOutputImage, TParentImageFilter>::GraftOutput(
  const DataObjectIdentifierType &              key,
  typename itk::CLETraits<TOutputImage>::Type * output)
{
  using CLEOutputImage = typename itk::CLETraits<TOutputImage>::Type;
  typename CLEOutputImage::Pointer cleImage = dynamic_cast<CLEOutputImage *>(this->ProcessObject::GetOutput(key));

  cleImage->Graft(output);
}

template <typename TInputImage, typename TOutputImage, typename TParentImageFilter>
void
CLEImageToImageFilter<TInputImage, TOutputImage, TParentImageFilter>::GraftOutput(const DataObjectIdentifierType & key,
                                                                                  DataObject * output)
{
  using CLEOutputImage = typename itk::CLETraits<TOutputImage>::Type;
  auto * cleImage = dynamic_cast<CLEOutputImage *>(output);
  if (cleImage)
  {
    this->GraftOutput(key, cleImage);
  }
  else
  {
    itkExceptionMacro(<< "itk::CLEImageToImageFilter::GraftOutput() cannot cast " << typeid(output).name() << " to "
                      << typeid(CLEOutputImage *).name());
  }
}

} // end namespace itk

#endif
