# CMake file for chap_08 example2

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_08_ex2 example2.cpp)

target_link_libraries(chap_08_ex2 GfxModule)
