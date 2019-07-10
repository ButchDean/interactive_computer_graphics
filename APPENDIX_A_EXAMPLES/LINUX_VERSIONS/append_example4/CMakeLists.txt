# CMake file for append example4

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex4 append_example4.cpp)

target_link_libraries(append_ex4 GfxModule)
