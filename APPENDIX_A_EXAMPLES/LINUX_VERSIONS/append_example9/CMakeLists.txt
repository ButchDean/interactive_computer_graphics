# CMake file for append example9

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex9 append_example9.cpp)

target_link_libraries(append_ex9 GfxModule)
