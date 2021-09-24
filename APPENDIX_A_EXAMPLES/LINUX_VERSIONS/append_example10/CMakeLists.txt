# CMake file for append example_a10

include_directories(${CMAKE_SOURCE_DIR}/include
		    ${CMAKE_SOURCE_DIR}/include/data)

add_executable(append_ex10 append_example_a10.cc)

target_link_libraries(append_ex10 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader_a10.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader_a10.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader_a10.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader_a10.glsl COPYONLY)
