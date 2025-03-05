cmake_minimum_required(VERSION 3.29)
project(JSON)

set(CMAKE_CXX_STANDARD 20)

add_executable(JSON main.cpp
                parser.cpp
                parser.h tokenizer.cpp tokenizer.h)
