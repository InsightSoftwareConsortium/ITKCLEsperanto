itk_module_test()

set(CLEsperantoTests
  itkMinimalStandardRandomVariateGeneratorTest.cxx
  itkMyFilterTest.cxx
  )

CreateTestDriver(CLEsperanto "${CLEsperanto-Test_LIBRARIES}" "${CLEsperantoTests}")

itk_add_test(NAME itkMinimalStandardRandomVariateGeneratorTest
  COMMAND CLEsperantoTestDriver itkMinimalStandardRandomVariateGeneratorTest
  )

itk_add_test(NAME itkMyFilterTest
  COMMAND CLEsperantoTestDriver
    --compare
    ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
    DATA{Baseline/itkMyFilterTestOutput.mha}
  itkMyFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  )
