# CMake file for chap_05 example2

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_05_ex2 example2.cpp)

target_link_libraries(chap_05_ex2 GfxModule)
