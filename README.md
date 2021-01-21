# Interactive Computer Graphics
## by Edward Angel

I have moved the build system from Make to CMake for various Linux distro compatibility, and have so far tested on Ubuntu/Pop_OS and RedHat/CentOS.

**Building the Project**

To default build it is advisable to create a build directory from project root directory and go into it:

```
$ mkdir build && cd build
```
Then once you are in there, do:

```
$ cmake .. && make
```
Note that you can speed up the build process if you are aware how many cores your CPU has and how many threads each of those cores can execute. For example, if I have a CPU with 4 cores (physical processing units) and each of those cores can run one thread each (4 x 1 = 4 logical processing units) I know that I can build my code 4x faster by using the '-j' option like this (using the last command as an example): 

```
$ cmake .. && make -j4
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

Dean Butcher (2019)
