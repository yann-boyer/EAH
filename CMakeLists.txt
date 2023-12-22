cmake_minimum_required(VERSION 3.25)

project(EAH)

file(GLOB_RECURSE HEADERS include/**.hpp)
file(GLOB_RECURSE SOURCES src/**.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)