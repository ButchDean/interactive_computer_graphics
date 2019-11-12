# CMake file for chap_05 example6

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chap_05_ex6 example6.cpp)

target_link_libraries(chap_05_ex6 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader56.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader56.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader56.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader56.glsl COPYONLY)
