itk_module_test()

message(STATUS "Adding Tests")

set(CLEsperantoTests
  itkCLEImageTest.cxx
  )

CreateTestDriver(CLEsperanto "${CLEsperanto-Test_LIBRARIES}" "${CLEsperantoTests}")

itk_add_test(NAME itkCLEImageTest
  COMMAND CLEsperantoTestDriver itkCLEImageTest
  )
