# CMake file for chap_02 example4

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_02_ex4 example4.cpp)

target_link_libraries(chap_02_ex4 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader24.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader24.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader24.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader24.glsl COPYONLY)
