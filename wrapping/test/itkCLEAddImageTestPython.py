#!/usr/bin/env python3

#==========================================================================
#
#   Copyright NumFOCUS
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          https://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/

import itertools

import itk
itk.auto_progress(2)
assert 'CLEAddImageFilter' in dir(itk)

# Set up images to add
width = 256
height = 256

default_value_1 = 2.0
default_value_2 = 1.0
expected_sum = 3.0

image_type = itk.CLEImage[itk.F,2]
def setup_image(width, height, default_value):
    image = image_type.New()
    image.DebugOn()
    image.SetRegions([width, height])
    image.Allocate()
    image.FillBuffer(default_value)
    return image

image1 = setup_image(width, height, default_value_1)
image2 = setup_image(width, height, default_value_2)

filter_type = itk.CLEAddImageFilter[image_type, image_type]
add_filter = filter_type.New()
add_filter.SetInput1(image1)
add_filter.SetInput2(image2)
add_filter.Update()

output_image = add_filter.GetOutput()
output_image.Update()

assert(itk.size(output_image) == [width, height])
assert(itk.spacing(output_image) == [1,1])
assert(itk.origin(output_image) == [0,0])

for i,j in itertools.product(range(width), range(height)):
    if(output_image.GetPixel([i,j])) != expected_sum:
        raise ValueError(f'{output_image.GetPixel([i,j])} != {expected_sum} at [{i},{j}]')
