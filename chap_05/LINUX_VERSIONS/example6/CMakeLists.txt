# CMake file for chap_05 example6

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_05_ex6 example6.cpp)

target_link_libraries(chap_05_ex6 GfxModule)
