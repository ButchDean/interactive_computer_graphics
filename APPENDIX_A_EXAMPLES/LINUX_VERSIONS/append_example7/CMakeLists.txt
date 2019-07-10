# CMake file for append example7

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex7 append_example7.cpp)

target_link_libraries(append_ex7 GfxModule)
