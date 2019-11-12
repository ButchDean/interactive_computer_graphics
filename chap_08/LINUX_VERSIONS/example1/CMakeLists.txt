# CMake file for chap_08 example1

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_08_ex1 example1.cpp)

target_link_libraries(chap_08_ex1 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader81.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader81.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader81.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader81.glsl COPYONLY)
