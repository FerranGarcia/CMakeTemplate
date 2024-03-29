cmake_minimum_required(VERSION 3.5)

# The version number.
set (Foo_VERSION_MAJOR 1)
set (Foo_VERSION_MINOR 0)

project(Foo LANGUAGES CXX VERSION ${Foo_VERSION_MAJOR}.${Foo_VERSION_MINOR})

option(FOO_BUILD_TESTS "Build Unit tests." ON)
option(FOO_BUILD_EXAMPLES "Build Examples." ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/FooConfig.hpp.in"
  "${PROJECT_BINARY_DIR}/FooConfig.hpp"
  )


# Add Boost
find_package(Boost 1.54 REQUIRED COMPONENTS regex)


# Build Tests
if(FOO_BUILD_TESTS)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/Catch2")
	enable_testing()
  	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
endif()

# Build Examples
if(FOO_BUILD_EXAMPLES)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/examples")
endif()


add_library(foo src/foo.cpp)
add_library(Foo::foo ALIAS foo)

target_include_directories(foo 
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
      ${CMAKE_SOURCE_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/src
      ${PROJECT_BINARY_DIR}
)

target_compile_features(foo PRIVATE cxx_auto_type)
target_compile_options(foo PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

target_link_libraries(foo
    PUBLIC
        Boost::boost
    PRIVATE
        
)

# Installation instructions
# Install library (.a or .so) and register in the export
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/foo)

install(TARGETS foo
    EXPORT foo-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name Foo and not foo
set_target_properties(foo PROPERTIES EXPORT_NAME Foo)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install the export defined above
install(EXPORT foo-targets
  FILE
    FooTargets.cmake
  NAMESPACE
    Foo::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/foo
)

# Import your targets inside your Config.cmake
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/FooConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/FooConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/FooConfig.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

## Exporting from the build tree
export(EXPORT foo-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/FooTargets.cmake NAMESPACE Foo::)

#Register package in user's package registry
export(PACKAGE Foo)