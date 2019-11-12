# CMake file for chap_09 example2

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_09_ex2 example2.cpp)

target_link_libraries(chap_09_ex2 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader92.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader92.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader92.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader92.glsl COPYONLY)
