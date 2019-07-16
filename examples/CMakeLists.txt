add_executable (example_main src/main.cpp)
target_link_libraries(example_main Foo::foo)