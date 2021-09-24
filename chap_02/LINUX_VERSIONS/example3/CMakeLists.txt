# CMake file for chap_02 example3

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_02_ex3 example3.cc)

target_link_libraries(chap_02_ex3 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader23.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader23.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader23.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader23.glsl COPYONLY)
