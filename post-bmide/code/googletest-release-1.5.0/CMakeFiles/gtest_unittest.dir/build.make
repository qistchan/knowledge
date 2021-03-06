# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /data/app/get/googletest-release-1.5.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/app/get/googletest-release-1.5.0

# Include any dependencies generated for this target.
include CMakeFiles/gtest_unittest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gtest_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gtest_unittest.dir/flags.make

CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o: CMakeFiles/gtest_unittest.dir/flags.make
CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o: test/gtest_unittest.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /data/app/get/googletest-release-1.5.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS)  -Wall -Wshadow -DGTEST_HAS_PTHREAD=1 -fexceptions -o CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o -c /data/app/get/googletest-release-1.5.0/test/gtest_unittest.cc

CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS)  -Wall -Wshadow -DGTEST_HAS_PTHREAD=1 -fexceptions -E /data/app/get/googletest-release-1.5.0/test/gtest_unittest.cc > CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.i

CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS)  -Wall -Wshadow -DGTEST_HAS_PTHREAD=1 -fexceptions -S /data/app/get/googletest-release-1.5.0/test/gtest_unittest.cc -o CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.s

CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o.requires:
.PHONY : CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o.requires

CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o.provides: CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o.requires
	$(MAKE) -f CMakeFiles/gtest_unittest.dir/build.make CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o.provides.build
.PHONY : CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o.provides

CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o.provides.build: CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o
.PHONY : CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o.provides.build

# Object files for target gtest_unittest
gtest_unittest_OBJECTS = \
"CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o"

# External object files for target gtest_unittest
gtest_unittest_EXTERNAL_OBJECTS =

gtest_unittest: CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o
gtest_unittest: libgtest_main.a
gtest_unittest: libgtest.a
gtest_unittest: CMakeFiles/gtest_unittest.dir/build.make
gtest_unittest: CMakeFiles/gtest_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable gtest_unittest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gtest_unittest.dir/build: gtest_unittest
.PHONY : CMakeFiles/gtest_unittest.dir/build

CMakeFiles/gtest_unittest.dir/requires: CMakeFiles/gtest_unittest.dir/test/gtest_unittest.cc.o.requires
.PHONY : CMakeFiles/gtest_unittest.dir/requires

CMakeFiles/gtest_unittest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gtest_unittest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gtest_unittest.dir/clean

CMakeFiles/gtest_unittest.dir/depend:
	cd /data/app/get/googletest-release-1.5.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/app/get/googletest-release-1.5.0 /data/app/get/googletest-release-1.5.0 /data/app/get/googletest-release-1.5.0 /data/app/get/googletest-release-1.5.0 /data/app/get/googletest-release-1.5.0/CMakeFiles/gtest_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gtest_unittest.dir/depend

