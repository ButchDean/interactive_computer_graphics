# CMake file for append example_a2

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex2 append_example_a2.cpp)

target_link_libraries(append_ex2 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader_a2.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader_a2.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader_a2.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader_a2.glsl COPYONLY)
