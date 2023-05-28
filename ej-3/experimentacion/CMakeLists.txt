cmake_minimum_required(VERSION 3.16)
project(experimentacion)

set(CMAKE_CXX_STANDARD 14)

add_executable(exp-denso
        ./algoritmos/modems.h
        ./algoritmos/impl/modems-denso.cpp
        experimento.cpp)
target_compile_definitions(exp-denso PUBLIC SRC=1)

add_executable(exp-dsu
        ./algoritmos/modems.h
        ./algoritmos/impl/modems-dsu.cpp
        experimento.cpp)
target_compile_definitions(exp-dsu PUBLIC SRC=2)

add_executable(exp-dsu-ingenuo
        ./algoritmos/modems.h
        ./algoritmos/impl/modems-dsu-ingenuo.cpp
        experimento.cpp)
target_compile_definitions(exp-dsu-ingenuo PUBLIC SRC=3)
