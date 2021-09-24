# CMake file for chap_04 example2

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_04_ex2 example2.cc)

target_link_libraries(chap_04_ex2 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader42.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader42.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader42.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader42.glsl COPYONLY)
