# CMake file for append example_a3

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex3 append_example_a3.cpp)

target_link_libraries(append_ex3 GfxModule)
