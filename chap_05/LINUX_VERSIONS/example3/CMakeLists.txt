# CMake file for chap_05 example3

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_05_ex3 example3.cpp)

target_link_libraries(chap_05_ex3 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader53.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader53.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader53.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader53.glsl COPYONLY)
