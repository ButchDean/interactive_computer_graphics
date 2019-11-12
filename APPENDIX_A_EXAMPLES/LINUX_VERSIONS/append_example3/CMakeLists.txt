# CMake file for append example_a3

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex3 append_example_a3.cpp)

target_link_libraries(append_ex3 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader_a3.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader_a3.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader_a3.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader_a3.glsl COPYONLY)
