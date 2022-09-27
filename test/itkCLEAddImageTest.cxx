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

#include "itkTestingMacros.h"
#include "itkMath.h"

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

  image1->FillBuffer(1.0f);
  image2->FillBuffer(2.0f);

  using AddImageFilterType = itk::CLEAddImageFilter<ImageType, ImageType>;
  
  auto addFilter = AddImageFilterType::New();
  addFilter->SetInput1(image1);
  addFilter->SetInput2(image2);
  addFilter->Update();

  return EXIT_SUCCESS;
}
