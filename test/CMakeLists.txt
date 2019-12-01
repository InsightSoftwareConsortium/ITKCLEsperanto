itk_module_test()

set(GPUTests
  itkMinimalStandardRandomVariateGeneratorTest.cxx
  itkMyFilterTest.cxx
  )

CreateTestDriver(GPU "${GPU-Test_LIBRARIES}" "${GPUTests}")

itk_add_test(NAME itkMinimalStandardRandomVariateGeneratorTest
  COMMAND GPUTestDriver itkMinimalStandardRandomVariateGeneratorTest
  )

itk_add_test(NAME itkMyFilterTest
  COMMAND GPUTestDriver
    --compare
    ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
    DATA{Baseline/itkMyFilterTestOutput.mha}
  itkMyFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  )
