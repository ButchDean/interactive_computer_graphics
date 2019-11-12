# CMake file for chap_03 example6

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_03_ex6 example6.cpp)

target_link_libraries(chap_03_ex6 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader36.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader36.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader36.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader36.glsl COPYONLY)
