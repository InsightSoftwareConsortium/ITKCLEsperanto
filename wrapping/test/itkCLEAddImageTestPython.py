#!/usr/bin/env python3

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
assert(itk.size(output_image) == [width, height])
assert(itk.spacing(output_image) == [1,1])
assert(itk.origin(output_image) == [0,0])

for i,j in itertools.product(range(width), range(height)):
    if(output_image.GetPixel([i,j])) != expected_sum:
        raise ValueError(f'{output_image.GetPixel([i,j])} != {expected_sum} at [{i},{j}]')
