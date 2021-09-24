# CMake file for append example_a5

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex5 append_example_a5.cc)

target_link_libraries(append_ex5 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader_a5.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader_a5.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader_a5.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader_a5.glsl COPYONLY)
