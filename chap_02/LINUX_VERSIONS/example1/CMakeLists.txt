# CMake file for chap_02 example1

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_02_ex1 example1.cc)

target_link_libraries(chap_02_ex1 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader21.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader21.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader21.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader21.glsl COPYONLY)
