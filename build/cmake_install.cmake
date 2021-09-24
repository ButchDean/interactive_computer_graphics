# Install script for directory: /home/deanbutcher/Documents/interactive_computer_graphics

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_02/LINUX_VERSIONS/example1/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_02/LINUX_VERSIONS/example2/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_02/LINUX_VERSIONS/example3/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_02/LINUX_VERSIONS/example4/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_02/LINUX_VERSIONS/example4b/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_02/LINUX_VERSIONS/example5/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_03/LINUX_VERSIONS/example1/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_03/LINUX_VERSIONS/example2/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_03/LINUX_VERSIONS/example6/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_04/LINUX_VERSIONS/example1/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_04/LINUX_VERSIONS/example2/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_04/LINUX_VERSIONS/example3/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_05/LINUX_VERSIONS/example1/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_05/LINUX_VERSIONS/example2/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_05/LINUX_VERSIONS/example3/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_05/LINUX_VERSIONS/example6/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_07/LINUX_VERSIONS/example1/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_07/LINUX_VERSIONS/example2/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_07/LINUX_VERSIONS/example3/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_08/LINUX_VERSIONS/example1/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_08/LINUX_VERSIONS/example2/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_08/LINUX_VERSIONS/example3/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_09/LINUX_VERSIONS/example1/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_09/LINUX_VERSIONS/example1_6E/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_09/LINUX_VERSIONS/example2/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_10/LINUX_VERSIONS/example1/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_10/LINUX_VERSIONS/example2/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_10/LINUX_VERSIONS/example3/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/chap_10/LINUX_VERSIONS/example4/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example2/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example3/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example4/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example5/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example6/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example7/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example8/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example9/cmake_install.cmake")
  include("/home/deanbutcher/Documents/interactive_computer_graphics/build/APPENDIX_A_EXAMPLES/LINUX_VERSIONS/append_example10/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/deanbutcher/Documents/interactive_computer_graphics/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
