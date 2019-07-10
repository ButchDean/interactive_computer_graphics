# CMake file for chap_09 example1_6E

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_09_ex1_6e chap09_6E_example1.cpp)

target_link_libraries(chap_09_ex1_6e GfxModule)
