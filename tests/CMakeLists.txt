add_executable(test_math tests/test_math.cpp)
target_include_directories(test_math PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME test_math COMMAND test_math)
