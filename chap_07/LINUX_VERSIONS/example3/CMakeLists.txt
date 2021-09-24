# CMake file for chap_07 example3

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_07_ex3 example3.cc)

target_link_libraries(chap_07_ex3 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader73.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader73.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader73.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader73.glsl COPYONLY)
