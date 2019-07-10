# CMake file for append example10

include_directories(${CMAKE_SOURCE_DIR}/include
		    ${CMAKE_SOURCE_DIR}/include/data)

add_executable(append_ex10 append_example10.cpp)

target_link_libraries(append_ex10 GfxModule)
