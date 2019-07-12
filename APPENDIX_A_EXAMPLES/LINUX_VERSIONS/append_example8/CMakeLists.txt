# CMake file for append example_a8

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex8 append_example_a8.cpp)

target_link_libraries(append_ex8 GfxModule)
