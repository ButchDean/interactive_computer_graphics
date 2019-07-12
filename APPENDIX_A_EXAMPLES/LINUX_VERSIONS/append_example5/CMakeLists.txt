# CMake file for append example_a5

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex5 append_example_a5.cpp)

target_link_libraries(append_ex5 GfxModule)
