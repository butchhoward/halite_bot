cmake_minimum_required(VERSION 2.8)

project(MyBot)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall -Wno-unused-function -pedantic")

include_directories(${CMAKE_SOURCE_DIR}/hlt)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    file(GLOB_RECURSE SOURCE ${dir}/*.[ch]*)
    set(SOURCE_FILES "${SOURCE_FILES}" ${SOURCE})
endforeach()

file(GLOB SOURCE ./*.cpp ./*.hpp)
set(SOURCE_FILES "${SOURCE_FILES}" ${SOURCE})

include_directories(${CMAKE_SOURCE_DIR})

message("====sources======")
foreach(srcfile ${SOURCE_FILES})
    message("${srcfile}") 
endforeach()

add_executable(MyBot ${SOURCE_FILES})
