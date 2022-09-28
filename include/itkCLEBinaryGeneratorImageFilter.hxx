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
#ifndef itkCLEBinaryGeneratorImageFilter_hxx
#define itkCLEBinaryGeneratorImageFilter_hxx


namespace itk
{

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::
  CLEBinaryGeneratorImageFilter()
{
  this->SetNumberOfRequiredInputs(2);
  this->InPlaceOff();
  this->DynamicMultiThreadingOff();
  this->ThreaderUpdateProgressOff();
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::SetInput1(
  const TInputImage1 * image1)
{
  // Process object is not const-correct so the const casting is required.
  this->SetNthInput(0, const_cast<TInputImage1 *>(image1));
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::SetInput1(
  const DecoratedInput1ImagePixelType * input1)
{
  // Process object is not const-correct so the const casting is required.
  this->SetNthInput(0, const_cast<DecoratedInput1ImagePixelType *>(input1));
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::SetInput1(
  const Input1ImagePixelType & input1)
{
  auto newInput = DecoratedInput1ImagePixelType::New();
  newInput->Set(input1);
  this->SetInput1(newInput);
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::SetConstant1(
  const Input1ImagePixelType & input1)
{
  this->SetInput1(input1);
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
auto
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::GetConstant1() const
  -> const Input1ImagePixelType &
{
  const auto * input = dynamic_cast<const DecoratedInput1ImagePixelType *>(this->ProcessObject::GetInput(0));
  if (input == nullptr)
  {
    itkExceptionMacro(<< "Constant 1 is not set");
  }
  return input->Get();
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::SetInput2(
  const TInputImage2 * image2)
{
  // Process object is not const-correct so the const casting is required.
  this->SetNthInput(1, const_cast<TInputImage2 *>(image2));
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::SetInput2(
  const DecoratedInput2ImagePixelType * input2)
{
  // Process object is not const-correct so the const casting is required.
  this->SetNthInput(1, const_cast<DecoratedInput2ImagePixelType *>(input2));
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::SetInput2(
  const Input2ImagePixelType & input2)
{
  auto newInput = DecoratedInput2ImagePixelType::New();
  newInput->Set(input2);
  this->SetInput2(newInput);
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::SetConstant2(
  const Input2ImagePixelType & input2)
{
  this->SetInput2(input2);
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
auto
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::GetConstant2() const
  -> const Input2ImagePixelType &
{
  const auto * input = dynamic_cast<const DecoratedInput2ImagePixelType *>(this->ProcessObject::GetInput(1));
  if (input == nullptr)
  {
    itkExceptionMacro(<< "Constant 2 is not set");
  }
  return input->Get();
}

template <typename TInputImage1, typename TInputImage2, typename TOutputImage, typename TParentImageFilter>
void
CLEBinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage, TParentImageFilter>::GenerateOutputInformation()
{

  const DataObject * input = nullptr;
  const auto *       inputPtr1 = dynamic_cast<const TInputImage1 *>(ProcessObject::GetInput(0));
  const auto *       inputPtr2 = dynamic_cast<const TInputImage2 *>(ProcessObject::GetInput(1));

  if (this->GetNumberOfInputs() >= 2)
  {
    if (inputPtr1)
    {
      input = inputPtr1;
    }
    else if (inputPtr2)
    {
      input = inputPtr2;
    }
    else
    {
      return;
    }

    for (unsigned int idx = 0; idx < this->GetNumberOfOutputs(); ++idx)
    {
      DataObject * output = this->GetOutput(idx);
      if (output)
      {
        output->CopyInformation(input);
      }
    }
  }
}

} // end of namespace itk

#endif
