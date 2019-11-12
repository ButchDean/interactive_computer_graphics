# CMake file for chap_10 example2

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(../include)

add_executable(chap_10_ex2 example2.cpp)

target_link_libraries(chap_10_ex2 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader102.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader102.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader102.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader102.glsl COPYONLY)
