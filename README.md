# Interactive Computer Graphics (Linux Versions)
## by Edward Angel

The code in this repo is the Linux version of the code. I have moved the build system from Make to CMake for various Linux distro compatibility, and have so far tested on Ubuntu/Pop_OS and RedHat/CentOS.

**Building the Project**

To default build it is advisable to create a build directory from project root directory and go into it:

```
$ mkdir build && cd build
```
Then once you are in there, do:

```
$ cmake .. && make
```
for sequential builds. If you want to use all available cores to build the project faster, you can do:

```
$ cmake .. && make -j$(nproc)
```
You also have a lot of control over what you want to build when. If you look at the CMakeLists.txt file in the project root you will see the following lines of code:

```
option(BUILD_CHAP_02 "Build Chap 02 subproject." ON)
option(BUILD_CHAP_03 "Build Chap 03 subproject." ON)
option(BUILD_CHAP_04 "Build Chap 04 subproject." ON)
option(BUILD_CHAP_05 "Build Chap 05 subproject." ON)
option(BUILD_CHAP_07 "Build Chap 07 subproject." ON)
option(BUILD_CHAP_08 "Build Chap 08 subproject." ON)
option(BUILD_CHAP_09 "Build Chap 09 subproject." ON)
option(BUILD_CHAP_10 "Build Chap 10 subproject." ON)
option(BUILD_APPEN_A "Build Appendix A subproject." ON)
```

where you have the option to cherrypick which projects you would like built. Alternatively, you can do the same from the command line, for example to not build the first Chapter 02 subproject you can do:

```
$ cmake -DBUILD_CHAP_02=OFF .. && make
```

**Where are the executables?**

The executables are grouped by chapter then example, so if you want chap04 example1 you follow the path:

```
build/chap_04/LINUX_VERSIONS/example1/
```

where you will find the executable:

```
chap_04_ex1
```

Any problems feel free to fork, fix then issue a pull request.

[Here is the link](http://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/) to the Mac and Windows original versions on Edward Angel's site.

Dean Butcher (2022)
