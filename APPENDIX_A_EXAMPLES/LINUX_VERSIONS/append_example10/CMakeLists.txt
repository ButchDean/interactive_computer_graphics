# CMake file for append example_a10

include_directories(${CMAKE_SOURCE_DIR}/include
		    ${CMAKE_SOURCE_DIR}/include/data)

add_executable(append_ex10 append_example_a10.cpp)

target_link_libraries(append_ex10 GfxModule)
