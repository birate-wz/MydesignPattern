cmake_minimum_required(VERSION 3.12)

project(designPattern)

set(CMAKE_CXX_STANDARD 20)

file(GLOB sources "*.cpp")
foreach(source IN LISTS sources)
    get_filename_component(name ${source} NAME_WE)
    add_executable(${name} ${source})
endforeach()
