# CMake file for append example_a8

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex8 append_example_a8.cc)

target_link_libraries(append_ex8 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader_a8.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader_a8.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader_a8.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader_a8.glsl COPYONLY)
