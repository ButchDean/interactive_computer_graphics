# CMake file for chap_10 example4

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(../include)

add_executable(chap_10_ex4 example4.cc)

target_link_libraries(chap_10_ex4 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader104.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader104.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader104.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader104.glsl COPYONLY)
