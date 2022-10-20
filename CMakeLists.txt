cmake_minimum_required(VERSION 3.16.3)
project(CLEsperanto)

#### Organizational Utility For MSVC Users ###############################
function(OrganizeTargets dir folder)
  get_all_targets_recursive(targets ${dir})
  foreach(t ${targets})
    get_target_property(f ${t} FOLDER)
    if(NOT f)
      set(f "")
    endif()
    set_target_properties (${t} PROPERTIES FOLDER "${folder}/${f}")
  endforeach()
endfunction()
macro(get_all_targets_recursive targets dir)
    get_property(subdirectories DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirectories})
        get_all_targets_recursive(${targets} ${subdir})
    endforeach()
    get_property(current_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${targets} ${current_targets})
endmacro()
########################################################################

# Libraries to link.
# See https://github.com/InsightSoftwareConsortium/ITK/blob/master/CMake/ITKModuleAPI.cmake
set(CLEsperanto_LIBRARIES CLEsperanto)

# Set position independent code on all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
message(STATUS "CMAKE_POSITION_INDEPENDENT_CODE IS ${CMAKE_POSITION_INDEPENDENT_CODE}")

# Enable/disable ITK/CLIc test suites independently.
# Note that clci inherits the value of BUILD_TESTING when clci is declared.
set(ITKCLEsperanto_BUILD_TESTING ${BUILD_TESTING})
option(CLIc_BUILD_TESTING OFF)
set(BUILD_TESTING ${CLIc_BUILD_TESTING})

# Get CLIc from development branch commit tag
set(CLIc_GIT_REPOSITORY "https://github.com/clEsperanto/CLIc_prototype.git")
set(CLIc_GIT_TAG        "2f3323e36504c0e14af9dcd796b24506e886cb86")

include(FetchContent)
FetchContent_Declare(
  clci
  GIT_REPOSITORY ${CLIc_GIT_REPOSITORY}
  GIT_TAG ${CLIc_GIT_TAG}
  )
FetchContent_MakeAvailable(clci)
OrganizeTargets(${clci_SOURCE_DIR} clci)


set(BUILD_TESTING ${ITKCLEsperanto_BUILD_TESTING})

set(CLEsperanto_INCLUDE_DIRS
  ${clci_SOURCE_DIR}
  ${clci_SOURCE_DIR}/clic/include/core
  ${clci_BINARY_DIR}/clic/include
  ${clci_SOURCE_DIR}/thirdparty/OpenCL-CLHPP/include/CL
  ${OpenCL_INCLUDE_DIR})

if(NOT ITK_SOURCE_DIR)
  find_package(ITK REQUIRED)
  list(APPEND CMAKE_MODULE_PATH ${ITK_CMAKE_DIR})
  # Create the module by processing itk-module.cmake
  include(ITKModuleExternal)
else()
  set(ITK_DIR ${CMAKE_BINARY_DIR})
  itk_module_impl()
endif()
