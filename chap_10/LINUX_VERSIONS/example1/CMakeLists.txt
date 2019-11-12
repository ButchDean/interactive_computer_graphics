# CMake file for chap_10 example1

include_directories(${CMAKE_SOURCE_DIR}/include
		    ${CMAKE_SOURCE_DIR}/include/data)

add_executable(chap_10_ex1 example1.cpp)

target_link_libraries(chap_10_ex1 GfxModule)

# Copy over shader files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fshader101.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/fshader101.glsl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vshader101.glsl
                ${CMAKE_CURRENT_BINARY_DIR}/vshader101.glsl COPYONLY)
