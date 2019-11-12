# CMake file for chap_04 example1

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_04_ex1 example1.cpp)

target_link_libraries(chap_04_ex1 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader41.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader41.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader41.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader41.glsl COPYONLY)
