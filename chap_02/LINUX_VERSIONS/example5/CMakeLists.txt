# CMake file for chap_02 example5

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_02_ex5 example5.cpp)

target_link_libraries(chap_02_ex5 GfxModule)
