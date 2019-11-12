# CMake file for chap_05 example2

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_05_ex2 example2.cpp)

target_link_libraries(chap_05_ex2 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader52.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader52.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader52.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader52.glsl COPYONLY)
