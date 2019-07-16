macro(foo_add_test TESTNAME)
  add_executable(${TESTNAME} ${ARGN})
  target_link_libraries(${TESTNAME} PRIVATE ${PROJECT_NAME}::foo)
  target_link_libraries(${TESTNAME} PRIVATE Catch2)
  add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
  set_target_properties(${TESTNAME} PROPERTIES FOLDER tests) 
endmacro()

foo_add_test(test_main "src/test_main.cpp")