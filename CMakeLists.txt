# OutputPrint class provides print() and println() methods 
# and String class from Wiring / Arduino library.
# Copyright (c) 2021 Jorge Rivera. All right reserved.
# License GNU Lesser General Public License v3.0.

cmake_minimum_required(VERSION 3.1)

project(outputprint)

# Set version number for shared libraries and executables
set(CU_VERSION 1.1) # current version
set(SO_VERSION 1.0) # compatibility version

# Set C++ Standard
set(CMAKE_CXX_STANDARD 11)

if(NOT BUILD_COMPILER)
  # Set complier identification
  SET(BUILD_COMPILER "${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}" )
  MESSAGE( STATUS "Compiler: " ${BUILD_COMPILER} )
endif()

# Check if has parent directory
get_directory_property(hasParent PARENT_DIRECTORY)

# Check if set CMAKE_BUILD_TYPE var
if(NOT CMAKE_BUILD_TYPE)
  # Set default build type to "release" set -O3 -DNDEBUG
  set(DEFAULT_BUILD_TYPE "release")
  SET(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE})
  MESSAGE( STATUS "Build type set to default: " ${CMAKE_BUILD_TYPE} )
else()
  # Check if set and valid CMAKE_BUILD_TYPE var
  STRING( TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE )
  if((CMAKE_BUILD_TYPE STREQUAL "debug") OR (CMAKE_BUILD_TYPE STREQUAL "release"))
    # If no has parent directory show message
    if(NOT hasParent)
      MESSAGE( STATUS "Build type set to: " ${CMAKE_BUILD_TYPE} )
    endif()
  else()
    MESSAGE( FATAL_ERROR "If set CMAKE_BUILD_TYPE it must be 'release' or 'debug'")
  endif()
endif()

# Setting build type to "debug" add only -g 
if(CMAKE_BUILD_TYPE STREQUAL "debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()

# Set C++ flags
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wconversion -Woverloaded-virtual -Wsign-conversion")
elseif(MSVC)
  set(MSVC_DISABLED_WARNINGS_LIST
    "C4996" # warning C4996: 'may be unsafe/disable deprecation'
            # To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
  )
  string(REPLACE "C" " -wd" MSVC_DISABLED_WARNINGS_STR ${MSVC_DISABLED_WARNINGS_LIST})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -WX -W4 ${MSVC_DISABLED_WARNINGS_STR}")
endif()


# Add source directory for sources
AUX_SOURCE_DIRECTORY( src/ ${PROJECT_NAME}_SRC ) 

# Add source directory for tools
AUX_SOURCE_DIRECTORY( tools/ TOOLS ) 

# Compile as object library
add_library( ${PROJECT_NAME}-obj OBJECT ${${PROJECT_NAME}_SRC} ${TOOLS} )

# Shared libraries need flag -fPIC
set_property(TARGET ${PROJECT_NAME}-obj PROPERTY POSITION_INDEPENDENT_CODE 1)

# Shared library built from the same object files 
# File extension OS depends, like: liboutputprint.so or liboutputprint.dylib or liboutputprint.dll
add_library( ${PROJECT_NAME}-dynamic SHARED $<TARGET_OBJECTS:${PROJECT_NAME}-obj> )
set_target_properties( ${PROJECT_NAME}-dynamic PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )

# Set version numbers for the versioned shared libraries target.
# For shared libraries and executables on Windows and Mach-O systems 
# the SOVERSION property corresponds to the compatibility version 
# and VERSION corresponds to the current version
# 
# Note that SOVERSION will still be used to form the install_name and 
# both SOVERSION and VERSION may also affect the file and symlink names.
# Use the NAMELINK_SKIP option of the install command to prevent the 
# generation of the versionless library name symbolic link to the 
# versioned library file.
set_target_properties( ${PROJECT_NAME}-dynamic PROPERTIES
		SOVERSION ${SO_VERSION}
		VERSION   ${CU_VERSION}
)

# Add static library liboutputprint.a
add_library( ${PROJECT_NAME} STATIC $<TARGET_OBJECTS:${PROJECT_NAME}-obj> )

# Add install targets
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(TARGETS ${PROJECT_NAME}-dynamic DESTINATION lib)

# If no has parent directory, add uninstall targets
if(NOT hasParent)
  MESSAGE(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
  add_custom_target( uninstall
      "${CMAKE_COMMAND}" -P "${CMAKE_SOURCE_DIR}/uninstall.cmake"
  )
endif()

# Add hello_world example, link static, no build as default 
add_executable( hello_world hello_world.cpp )
target_link_libraries( hello_world PRIVATE ${PROJECT_NAME} )
set_target_properties( hello_world PROPERTIES EXCLUDE_FROM_ALL TRUE )
