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
assert 'CLEsperanto' in dir(itk)

width = 256
height = 256

# Set up image
image_type = itk.CLEImage[itk.F,2]
image_0 = image_type.New()
print(image_0)

# Test Graft
image_1 = image_type.New()
image_1.SetRegions([width,height])
image_1.Allocate()

image_0.Graft(image_1)
if image_0.GetPixelContainer() != image_1.GetPixelContainer():
    raise ValueError('Graft test failed')

# Test FillBuffer
fill_value = 1.0
image_1.FillBuffer(fill_value)

for i,j in itertools.product(range(width), range(height)):
    assert image_1.GetPixel([i,j]) == fill_value

# Test SetPixel
index = [0,0]
set_value = 7.0
image_1.SetPixel(index, set_value)
for i,j in itertools.product(range(width), range(height)):
    if [i,j] == index:
        assert image_1.GetPixel([i,j]) == set_value
    else:
        assert image_1.GetPixel([i,j]) == fill_value

