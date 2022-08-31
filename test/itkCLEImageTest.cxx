/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkCLEImage.h"

#include "itkTestingMacros.h"
#include "itkMath.h"

#include "itkTestingComparisonImageFilter.h"

template <typename ImageType>
bool Compare(itk::SmartPointer<ImageType> b, itk::SmartPointer<ImageType> t)
{
  double        toleranceIntensity = 0.0;
  unsigned int  toleranceRadius = 0;
  unsigned long toleranceNumberOfPixels = 0;

  using DiffType = itk::Testing::ComparisonImageFilter<ImageType, ImageType>;

  // Setup our testing filter
  auto diff = DiffType::New();
  diff->SetValidInput(b);
  diff->SetTestInput(t);

  diff->SetDifferenceThreshold(toleranceIntensity);
  diff->SetToleranceRadius(toleranceRadius);

  diff->UpdateLargestPossibleRegion();

  bool differenceFailed = false;

  const double averageIntensityDifference = diff->GetTotalDifference();

  const unsigned long numberOfPixelsWithDifferences = diff->GetNumberOfPixelsWithDifferences();

  if (averageIntensityDifference > 0.0)
  {
    if (static_cast<int>(numberOfPixelsWithDifferences) > toleranceNumberOfPixels)
    {
      differenceFailed = true;
    }
    else
    {
      differenceFailed = false;
    }
  }
  else
  {
    differenceFailed = false;
  }

  return differenceFailed;
}

int itkCLEImageTest(int argc, char* argv[])
{
  if (argc > 1)
  {
    std::cout << "received " << argc << " arguments, but didn't expect any."
      << "first ignored argument: " << argv[1] << std::endl;
  }
  unsigned int width, height;
  using ImageType = itk::CLEImage<float, 2>;

  auto cleImage = ImageType::New();
  ITK_EXERCISE_BASIC_OBJECT_METHODS(cleImage, CLEImage, Image)

  std::cout << "Print: " << std::endl;
  cleImage->Print(std::cout);

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
  auto srcA = ImageType::New();
  auto srcB = ImageType::New();
  srcB->DebugOn();
  srcA->SetRegions(region);
  srcA->Allocate();
  srcB->SetRegions(region);
  srcB->Allocate();
  float B, Expected;// Temp testing variables

  // Ensure graft works
  std::cout << "Test Graft." << std::endl;
  cleImage->Graft(srcA);
  if (cleImage->GetPixelContainer() != cleImage->GetPixelContainer())
  {
    std::cerr << "Graft test failed." << std::endl;
    return EXIT_FAILURE;
  }

  // Testing FillBuffer
  Expected = 1.0f;
  srcA->FillBuffer(Expected);
  srcB->FillBuffer(Expected);
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);
  if (Compare<ImageType>(srcA, srcB))
    return EXIT_FAILURE;
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);

  // Testing SetPixel
  Expected = 7.0f;
  srcA->SetPixel(idx, Expected);
  srcB->SetPixel(idx, Expected);
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);
  if (Compare<ImageType>(srcA, srcB))
    return EXIT_FAILURE;
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);

  // Testing operator[]
  Expected = 22.0f;
  auto pixA = (*srcA)[idx];
  auto pixB = (*srcB)[idx];
  pixA = Expected;
  pixB = Expected;
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);
  if (Compare<ImageType>(srcA, srcB))
    return EXIT_FAILURE;
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);

  // Testing GetBufferPointer
  Expected = 12.0f;
  auto bufptrA = srcA->GetBufferPointer();
  auto bufptrB = srcB->GetBufferPointer();
  bufptrA[5] = Expected;
  bufptrB[5] = Expected;
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);
  if (Compare<ImageType>(srcA, srcB))
    return EXIT_FAILURE;
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);

  // Testing GetPixelContainer
  Expected = 55.0f;
  auto pxlCtrA = srcA->GetPixelContainer();
  auto pxlCtrB = srcB->GetPixelContainer();
  (*pxlCtrA)[7] = Expected;
  (*pxlCtrB)[7] = Expected;
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);
  if (Compare<ImageType>(srcA, srcB))
    return EXIT_FAILURE;
  B = srcB->GetPixel(idx);
  ITK_TEST_EXPECT_EQUAL(B, Expected);

  return EXIT_SUCCESS;
}
