# CMake file for chap_05 example1

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_05_ex1 example1.cc)

target_link_libraries(chap_05_ex1 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader51.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader51.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader51.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader51.glsl COPYONLY)
