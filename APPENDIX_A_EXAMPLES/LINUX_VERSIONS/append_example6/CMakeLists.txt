# CMake file for append example_a6

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex6 append_example_a6.cpp)

target_link_libraries(append_ex6 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader_a6.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader_a6.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader_a6.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader_a6.glsl COPYONLY)
