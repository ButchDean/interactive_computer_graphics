# CMake file for append example2

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex2 append_example2.cpp)

target_link_libraries(append_ex2 GfxModule)
