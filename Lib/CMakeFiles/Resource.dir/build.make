# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/MN_v01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/MN_v01

# Include any dependencies generated for this target.
include Lib/CMakeFiles/Resource.dir/depend.make

# Include the progress variables for this target.
include Lib/CMakeFiles/Resource.dir/progress.make

# Include the compile flags for this target's objects.
include Lib/CMakeFiles/Resource.dir/flags.make

Lib/CMakeFiles/Resource.dir/resource.cpp.o: Lib/CMakeFiles/Resource.dir/flags.make
Lib/CMakeFiles/Resource.dir/resource.cpp.o: Lib/resource.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/MN_v01/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Lib/CMakeFiles/Resource.dir/resource.cpp.o"
	cd /home/pi/MN_v01/Lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Resource.dir/resource.cpp.o -c /home/pi/MN_v01/Lib/resource.cpp

Lib/CMakeFiles/Resource.dir/resource.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Resource.dir/resource.cpp.i"
	cd /home/pi/MN_v01/Lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/MN_v01/Lib/resource.cpp > CMakeFiles/Resource.dir/resource.cpp.i

Lib/CMakeFiles/Resource.dir/resource.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Resource.dir/resource.cpp.s"
	cd /home/pi/MN_v01/Lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/MN_v01/Lib/resource.cpp -o CMakeFiles/Resource.dir/resource.cpp.s

Lib/CMakeFiles/Resource.dir/resource.cpp.o.requires:

.PHONY : Lib/CMakeFiles/Resource.dir/resource.cpp.o.requires

Lib/CMakeFiles/Resource.dir/resource.cpp.o.provides: Lib/CMakeFiles/Resource.dir/resource.cpp.o.requires
	$(MAKE) -f Lib/CMakeFiles/Resource.dir/build.make Lib/CMakeFiles/Resource.dir/resource.cpp.o.provides.build
.PHONY : Lib/CMakeFiles/Resource.dir/resource.cpp.o.provides

Lib/CMakeFiles/Resource.dir/resource.cpp.o.provides.build: Lib/CMakeFiles/Resource.dir/resource.cpp.o


Lib/CMakeFiles/Resource.dir/JSON.cpp.o: Lib/CMakeFiles/Resource.dir/flags.make
Lib/CMakeFiles/Resource.dir/JSON.cpp.o: Lib/JSON.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/MN_v01/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Lib/CMakeFiles/Resource.dir/JSON.cpp.o"
	cd /home/pi/MN_v01/Lib && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Resource.dir/JSON.cpp.o -c /home/pi/MN_v01/Lib/JSON.cpp

Lib/CMakeFiles/Resource.dir/JSON.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Resource.dir/JSON.cpp.i"
	cd /home/pi/MN_v01/Lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/MN_v01/Lib/JSON.cpp > CMakeFiles/Resource.dir/JSON.cpp.i

Lib/CMakeFiles/Resource.dir/JSON.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Resource.dir/JSON.cpp.s"
	cd /home/pi/MN_v01/Lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/MN_v01/Lib/JSON.cpp -o CMakeFiles/Resource.dir/JSON.cpp.s

Lib/CMakeFiles/Resource.dir/JSON.cpp.o.requires:

.PHONY : Lib/CMakeFiles/Resource.dir/JSON.cpp.o.requires

Lib/CMakeFiles/Resource.dir/JSON.cpp.o.provides: Lib/CMakeFiles/Resource.dir/JSON.cpp.o.requires
	$(MAKE) -f Lib/CMakeFiles/Resource.dir/build.make Lib/CMakeFiles/Resource.dir/JSON.cpp.o.provides.build
.PHONY : Lib/CMakeFiles/Resource.dir/JSON.cpp.o.provides

Lib/CMakeFiles/Resource.dir/JSON.cpp.o.provides.build: Lib/CMakeFiles/Resource.dir/JSON.cpp.o


# Object files for target Resource
Resource_OBJECTS = \
"CMakeFiles/Resource.dir/resource.cpp.o" \
"CMakeFiles/Resource.dir/JSON.cpp.o"

# External object files for target Resource
Resource_EXTERNAL_OBJECTS =

Lib/libResource.a: Lib/CMakeFiles/Resource.dir/resource.cpp.o
Lib/libResource.a: Lib/CMakeFiles/Resource.dir/JSON.cpp.o
Lib/libResource.a: Lib/CMakeFiles/Resource.dir/build.make
Lib/libResource.a: Lib/CMakeFiles/Resource.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/MN_v01/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libResource.a"
	cd /home/pi/MN_v01/Lib && $(CMAKE_COMMAND) -P CMakeFiles/Resource.dir/cmake_clean_target.cmake
	cd /home/pi/MN_v01/Lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Resource.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Lib/CMakeFiles/Resource.dir/build: Lib/libResource.a

.PHONY : Lib/CMakeFiles/Resource.dir/build

Lib/CMakeFiles/Resource.dir/requires: Lib/CMakeFiles/Resource.dir/resource.cpp.o.requires
Lib/CMakeFiles/Resource.dir/requires: Lib/CMakeFiles/Resource.dir/JSON.cpp.o.requires

.PHONY : Lib/CMakeFiles/Resource.dir/requires

Lib/CMakeFiles/Resource.dir/clean:
	cd /home/pi/MN_v01/Lib && $(CMAKE_COMMAND) -P CMakeFiles/Resource.dir/cmake_clean.cmake
.PHONY : Lib/CMakeFiles/Resource.dir/clean

Lib/CMakeFiles/Resource.dir/depend:
	cd /home/pi/MN_v01 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/MN_v01 /home/pi/MN_v01/Lib /home/pi/MN_v01 /home/pi/MN_v01/Lib /home/pi/MN_v01/Lib/CMakeFiles/Resource.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Lib/CMakeFiles/Resource.dir/depend

