# Root cmake file for project.

cmake_minimum_required(VERSION 2.8.0)

project(interactive_computer_graphics)

option(BUILD_CHAP_02 "Build Chap 02 subproject." ON)
option(BUILD_CHAP_03 "Build Chap 03 subproject." ON)
option(BUILD_CHAP_04 "Build Chap 04 subproject." ON)
option(BUILD_CHAP_05 "Build Chap 05 subproject." ON)
option(BUILD_CHAP_07 "Build Chap 07 subproject." ON)
option(BUILD_CHAP_08 "Build Chap 08 subproject." ON)
option(BUILD_CHAP_09 "Build Chap 09 subproject." ON)
option(BUILD_CHAP_10 "Build Chap 10 subproject." ON)
option(BUILD_APPEN_A "Build Appendix A subproject." ON)

ADD_LIBRARY(GfxModule
    ${CMAKE_SOURCE_DIR}/common/InitShader.cpp
)

target_link_libraries(GfxModule -lglut)
target_link_libraries(GfxModule -lGLEW)
target_link_libraries(GfxModule -lGL)
target_link_libraries(GfxModule -lGLU)

if(BUILD_CHAP_02)
    add_subdirectory(chap_02/LINUX_VERSIONS/example1)
    add_subdirectory(chap_02/LINUX_VERSIONS/example2)
    add_subdirectory(chap_02/LINUX_VERSIONS/example3)
    add_subdirectory(chap_02/LINUX_VERSIONS/example4)
    add_subdirectory(chap_02/LINUX_VERSIONS/example4b)
    add_subdirectory(chap_02/LINUX_VERSIONS/example5)
endif()

if(BUILD_CHAP_03)
    add_subdirectory(chap_03/LINUX_VERSIONS/example1)
    add_subdirectory(chap_03/LINUX_VERSIONS/example2)
    add_subdirectory(chap_03/LINUX_VERSIONS/example6)
endif()

if(BUILD_CHAP_04)
    add_subdirectory(chap_04/LINUX_VERSIONS/example1)
    add_subdirectory(chap_04/LINUX_VERSIONS/example2)
    add_subdirectory(chap_04/LINUX_VERSIONS/example3)
endif()

if(BUILD_CHAP_05)
    add_subdirectory(chap_05/LINUX_VERSIONS/example1)
    add_subdirectory(chap_05/LINUX_VERSIONS/example2)
    add_subdirectory(chap_05/LINUX_VERSIONS/example3)
    add_subdirectory(chap_05/LINUX_VERSIONS/example6)
endif()

if(BUILD_CHAP_07)
    add_subdirectory(chap_07/LINUX_VERSIONS/example1)
    add_subdirectory(chap_07/LINUX_VERSIONS/example2)
    add_subdirectory(chap_07/LINUX_VERSIONS/example3)
endif()

if(BUILD_CHAP_08)
    add_subdirectory(chap_08/LINUX_VERSIONS/example1)
    add_subdirectory(chap_08/LINUX_VERSIONS/example2)
    add_subdirectory(chap_08/LINUX_VERSIONS/example3)
endif()

if(BUILD_CHAP_09)
    add_subdirectory(chap_09/LINUX_VERSIONS/example1)
    add_subdirectory(chap_09/LINUX_VERSIONS/example1_6E)
    add_subdirectory(chap_09/LINUX_VERSIONS/example2)
endif()

if(BUILD_CHAP_10)
    add_subdirectory(chap_10/LINUX_VERSIONS/example1)
    add_subdirectory(chap_10/LINUX_VERSIONS/example2)
endif()

if(BUILD_APPEN_A)
    add_subdirectory(APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example2)
    add_subdirectory(APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example3)
    add_subdirectory(APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example4)
    add_subdirectory(APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example5)
    add_subdirectory(APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example6)
    add_subdirectory(APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example7)
    add_subdirectory(APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example8)
    add_subdirectory(APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example9)
    add_subdirectory(APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example10)
endif()
