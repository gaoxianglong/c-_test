cmake_minimum_required(VERSION 3.29)
project(c__test)

set(CMAKE_CXX_STANDARD 20)

add_executable(c__test main.cpp
        Account.cpp
        Account.h
        PimplTest.cpp
        PimplTest.h
)
