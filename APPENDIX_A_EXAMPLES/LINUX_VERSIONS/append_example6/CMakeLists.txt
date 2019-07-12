# CMake file for append example_a6

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex6 append_example_a6.cpp)

target_link_libraries(append_ex6 GfxModule)
