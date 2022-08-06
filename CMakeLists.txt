cmake_minimum_required(VERSION 3.10)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Vendor/fmt")

project(Hermod)

file(GLOB_RECURSE HERMOD_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h")
file(GLOB_RECURSE HERMOD_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")
add_library(Hermod SHARED "${HERMOD_HEADERS}" "${HERMOD_SOURCES}")

set_target_properties(Hermod PROPERTIES
    CXX_STANDARD 17
    LINKER_LANGUAGE CXX)

target_link_libraries(Hermod PUBLIC fmt::fmt-header-only)

target_include_directories(Hermod PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/Public")
target_include_directories(Hermod PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/Private")

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "cmake/HermodConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/HermodConfig.cmake"
    INSTALL_DESTINATION lib/Foo/cmake
)

write_basic_package_version_file(
	"HermodConfigVersion.cmake"
	VERSION 1.0.0
	COMPATIBILITY SameMajorVersion
)