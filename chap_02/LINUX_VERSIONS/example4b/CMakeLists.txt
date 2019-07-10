# CMake file for chap_02 example4b

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_02_ex4b example4b.cpp)

target_link_libraries(chap_02_ex4b GfxModule)
