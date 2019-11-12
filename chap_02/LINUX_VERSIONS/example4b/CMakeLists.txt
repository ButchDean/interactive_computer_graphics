# CMake file for chap_02 example4b

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_02_ex4b example4b.cpp)

target_link_libraries(chap_02_ex4b GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader24b.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader24b.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader24b.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader24b.glsl COPYONLY)
