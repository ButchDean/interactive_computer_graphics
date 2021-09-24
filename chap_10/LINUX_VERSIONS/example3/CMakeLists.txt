# CMake file for chap_10 example3

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(../include)

add_executable(chap_10_ex3 example3.cc)

target_link_libraries(chap_10_ex3 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader103.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader103.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader103.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader103.glsl COPYONLY)
