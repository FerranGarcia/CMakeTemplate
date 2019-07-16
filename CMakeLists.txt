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
