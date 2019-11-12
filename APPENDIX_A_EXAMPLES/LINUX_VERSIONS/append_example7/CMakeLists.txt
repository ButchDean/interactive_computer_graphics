# CMake file for append example_a7

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(append_ex7 append_example_a7.cpp)

target_link_libraries(append_ex7 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader_a7.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader_a7.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader_a7.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader_a7.glsl COPYONLY)
