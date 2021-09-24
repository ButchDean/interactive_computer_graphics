# CMake file for chap_03 example2

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_03_ex2 example2.cc)

target_link_libraries(chap_03_ex2 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader32.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader32.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader32.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader32.glsl COPYONLY)
