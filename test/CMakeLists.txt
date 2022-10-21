itk_module_test()

message(STATUS "Adding Tests")

set(CLEsperantoTests
  itkCLEImageTest.cxx
  itkCLEAddImageTest.cxx
  )

CreateTestDriver(CLEsperanto "${CLEsperanto-Test_LIBRARIES}" "${CLEsperantoTests}")

itk_add_test(NAME itkCLEImageTest
  COMMAND CLEsperantoTestDriver itkCLEImageTest
  )
itk_add_test(NAME itkCLEAddImageTest
  COMMAND CLEsperantoTestDriver itkCLEAddImageTest
  )
