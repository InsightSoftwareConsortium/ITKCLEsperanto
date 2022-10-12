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

#include "itkCLEAddImageFilter.h"

#include "itkImageRegionIteratorWithIndex.h"
#include "itkMath.h"
#include "itkTestingMacros.h"

int
itkCLEAddImageTest(int argc, char * argv[])
{
  if (argc > 1)
  {
    std::cout << "received " << argc << " arguments, but didn't expect any."
              << "first ignored argument: " << argv[1] << std::endl;
  }
  unsigned int width, height;
  using ImageType = itk::CLEImage<float, 2>;

  // set size & region
  width = 256;
  height = 256;
  ImageType::IndexType start;
  start[0] = 0;
  start[1] = 0;
  ImageType::SizeType size;
  size[0] = width;
  size[1] = height;
  ImageType::RegionType region;
  region.SetSize(size);
  region.SetIndex(start);
  ImageType::IndexType idx;
  idx[0] = 0;
  idx[1] = 0;
  // setup our images
  auto image1 = ImageType::New();
  auto image2 = ImageType::New();
  image1->DebugOn();
  image2->DebugOn();
  image1->SetRegions(region);
  image1->Allocate();
  image2->SetRegions(region);
  image2->Allocate();

  constexpr float value1 = 2.0;
  constexpr float value2 = 1.0;
  image1->FillBuffer(value1);
  image2->FillBuffer(value2);

  using AddImageFilterType = itk::CLEAddImageFilter<ImageType>;

  auto addFilter = AddImageFilterType::New();
  addFilter->SetInput1(image1);
  addFilter->SetInput2(image2);
  // Execute the filter
  ITK_TRY_EXPECT_NO_EXCEPTION(addFilter->Update());

  // Get the filter output
  ImageType::Pointer outputImage = addFilter->GetOutput();

  // Since we don't pass the outputImage to another processor/filter
  // A manual update of the image is required to sync gpu to cpu
  outputImage->Update();

  using OutputImageIteratorType = itk::ImageRegionIteratorWithIndex<ImageType>;
  // Create an iterator for going through the image output
  OutputImageIteratorType oIt(outputImage, outputImage->GetBufferedRegion());
  // Check the content of the result image
  const auto expectedValue = static_cast<ImageType::PixelType>(value1 + value2);
  while (!oIt.IsAtEnd())
  {
    if (!itk::Math::ExactlyEquals(oIt.Get(), expectedValue))
    {
      std::cerr << "Test failed!" << std::endl;
      std::cerr << "Error in pixel value at index [" << oIt.GetIndex() << "]" << std::endl;
      std::cerr << "Expected: " << expectedValue << ", but got: " << oIt.Get() << std::endl;
      return EXIT_FAILURE;
    }
    ++oIt;
  }

  return EXIT_SUCCESS;
}
