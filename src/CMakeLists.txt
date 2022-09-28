file(GLOB CLEsperanto_HDRS ../include/*.*)
message(STATUS "Headers: ${CLEsperanto_HDRS}")

set(CLEsperanto_SRCS
  itkCLEContextManager.cxx
  )

itk_module_add_library(CLEsperanto ${CLEsperanto_SRCS} ${CLEsperanto_HDRS})
target_link_libraries(CLEsperanto PUBLIC CLIc)
