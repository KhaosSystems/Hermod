project(Example)
add_executable(Example "${CMAKE_CURRENT_SOURCE_DIR}/Example/main.cpp")
set_target_properties(Example PROPERTIES CXX_STANDARD 20)
target_link_libraries(Example PUBLIC Hermod)