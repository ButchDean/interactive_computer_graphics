# CMake file for append example_a4

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex4 append_example_a4.cpp)

target_link_libraries(append_ex4 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader_a4.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader_a4.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader_a4.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader_a4.glsl COPYONLY)
