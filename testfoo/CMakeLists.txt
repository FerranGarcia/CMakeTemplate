cmake_minimum_required(VERSION 3.5)
project(external_test VERSION 0.0.1 LANGUAGES CXX)

add_executable(external_test src/main.cpp)
target_compile_features(external_test PRIVATE cxx_auto_type)

find_package(Foo REQUIRED)
target_link_libraries(external_test Foo::Foo)
