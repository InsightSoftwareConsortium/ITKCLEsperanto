itk_wrap_module(CLEsperanto)

set(WRAPPER_SUBMODULE_ORDER
  itkCLEDataManager
  itkCLEImageDataManager
  itkCLEImage
  itkCLEBaseClasses
  itkCLEImageToImageFilter
  itkCLEInPlaceImageFilter
  itkCLEBinaryGeneratorImageFilter
  itkCLEAddImageFilter
)

itk_auto_load_submodules()
itk_end_wrap_module()
