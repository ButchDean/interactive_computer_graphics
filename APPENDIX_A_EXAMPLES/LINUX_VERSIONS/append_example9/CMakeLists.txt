# CMake file for append example_a9

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex9 append_example_a9.cc)

target_link_libraries(append_ex9 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader_a9.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader_a9.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader_a9.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader_a9.glsl COPYONLY)
