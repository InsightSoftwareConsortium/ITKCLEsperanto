cmake_minimum_required(VERSION 3.10.2)
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

# What is this for?
set(CLEsperanto_LIBRARIES CLEsperanto)

# Get CLIc
set(CLIc_GIT_REPOSITORY "https://github.com/aaron-bray/CLIc_prototype.git")
set(CLIc_GIT_TAG        "cmake_updates")

include(FetchContent)
FetchContent_Declare(
  clci
  GIT_REPOSITORY ${CLIc_GIT_REPOSITORY}
  GIT_TAG ${CLIc_GIT_TAG}
  )
FetchContent_MakeAvailable(clci)
include_directories(SYSTEM ${clci_SOURCE_DIR})
OrganizeTargets(${clci_SOURCE_DIR} clci)

if(NOT ITK_SOURCE_DIR)
  find_package(ITK REQUIRED)
  list(APPEND CMAKE_MODULE_PATH ${ITK_CMAKE_DIR})
# Create the module by processing itk-module.cmake
include(ITKModuleExternal)
else()
  set(ITK_DIR ${CMAKE_BINARY_DIR})
  itk_module_impl()
endif()