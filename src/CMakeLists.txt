set(CLEsperanto_SRCS
  itkCLEContextManager.cxx
  )

itk_module_add_library(CLEsperanto ${CLEsperanto_SRCS})
target_link_libraries(CLEsperanto PUBLIC CLIc)
