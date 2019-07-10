# CMake file for chap_09 example1

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_09_ex1 example1.cpp)

target_link_libraries(chap_09_ex1 GfxModule)
