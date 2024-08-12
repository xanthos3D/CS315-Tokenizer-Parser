cmake_minimum_required(VERSION 3.24)
project(project1_phase2)

set(CMAKE_CXX_STANDARD 17)

add_executable(project1_phase2 main.cpp Token.cpp Token.hpp Tokenizer.cpp Tokenizer.hpp OpenTagStack.cpp OpenTagStack.hpp CompletedTags.cpp CompletedTags.hpp)
