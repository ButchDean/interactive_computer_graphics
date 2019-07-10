# CMake file for chap_04 example1

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_04_ex1 example1.cpp)

target_link_libraries(chap_04_ex1 GfxModule)
