itk_module_test()

set(OpenCLTests
  itkMinimalStandardRandomVariateGeneratorTest.cxx
  itkMyFilterTest.cxx
  )

CreateTestDriver(OpenCL "${OpenCL-Test_LIBRARIES}" "${OpenCLTests}")

itk_add_test(NAME itkMinimalStandardRandomVariateGeneratorTest
  COMMAND OpenCLTestDriver itkMinimalStandardRandomVariateGeneratorTest
  )

itk_add_test(NAME itkMyFilterTest
  COMMAND OpenCLTestDriver
    --compare
    ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
    DATA{Baseline/itkMyFilterTestOutput.mha}
  itkMyFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  )
