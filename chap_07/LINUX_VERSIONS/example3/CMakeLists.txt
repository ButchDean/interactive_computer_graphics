# CMake file for chap_07 example3

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_07_ex3 example3.cpp)

target_link_libraries(chap_07_ex3 GfxModule)
