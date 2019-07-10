# CMake file for chap_05 example3

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_05_ex3 example3.cpp)

target_link_libraries(chap_05_ex3 GfxModule)
