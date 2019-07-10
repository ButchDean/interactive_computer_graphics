# CMake file for chap_10 example1

include_directories(${CMAKE_SOURCE_DIR}/include
		    ${CMAKE_SOURCE_DIR}/include/data)

add_executable(chap_10_ex1 example1.cpp)

target_link_libraries(chap_10_ex1 GfxModule)
