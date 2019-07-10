# CMake file for chap_04 example3

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_04_ex3 example3.cpp)

target_link_libraries(chap_04_ex3 GfxModule)
