set(GPU_SRCS
  itkMinimalStandardRandomVariateGenerator.cxx
  )

itk_module_add_library(GPU ${GPU_SRCS})
