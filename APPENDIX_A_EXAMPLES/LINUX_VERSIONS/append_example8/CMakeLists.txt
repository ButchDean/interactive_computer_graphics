# CMake file for append example8

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex8 append_example8.cpp)

target_link_libraries(append_ex8 GfxModule)
