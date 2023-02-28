cmake_minimum_required(VERSION 3.24)
project(C__20Test)

set(CMAKE_CXX_STANDARD 20)

add_executable(C__20Test main.cpp template_module.cpp util.cpp template_module.h optional_test.cpp optional_test.h union_test.h union_test.cpp dfs797.cpp dfs797.h forwardTest.cpp forwardTest.h)
