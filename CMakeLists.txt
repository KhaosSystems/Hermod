cmake_minimum_required(VERSION 3.10)

add_subdirectory("${CMAKE_SOURCE_DIR}/Vendor/fmt")

project(Hermod)

file(GLOB_RECURSE HERMOD_HEADERS "${CMAKE_SOURCE_DIR}/Source/*.h")
file(GLOB_RECURSE HERMOD_SOURCES "${CMAKE_SOURCE_DIR}/Source/*.cpp")
file(GLOB_RECURSE HERMOD_MODULES "${CMAKE_SOURCE_DIR}/Source/*.ixx")
add_executable(Hermod "${HERMOD_HEADERS}" "${HERMOD_SOURCES}" "${HERMOD_MODULES}")

set_target_properties(Hermod PROPERTIES CXX_STANDARD 20)

target_link_libraries(Hermod PUBLIC fmt::fmt-header-only)

target_include_directories(Hermod PUBLIC "${CMAKE_SOURCE_DIR}/Source")