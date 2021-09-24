# CMake file for chap_09 example1

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_09_ex1 example1.cc)

target_link_libraries(chap_09_ex1 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader91.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader91.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader91.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader91.glsl COPYONLY)
