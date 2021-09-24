# CMake file for chap_02 example5

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_02_ex5 example5.cc)

target_link_libraries(chap_02_ex5 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader25.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader25.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader25.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader25.glsl COPYONLY)
