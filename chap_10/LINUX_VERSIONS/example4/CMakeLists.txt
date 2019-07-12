# CMake file for chap_10 example4

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(../include)

add_executable(chap_10_ex4 example4.cpp)

target_link_libraries(chap_10_ex4 GfxModule)
