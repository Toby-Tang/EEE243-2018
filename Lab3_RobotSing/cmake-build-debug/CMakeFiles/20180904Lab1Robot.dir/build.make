# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.1.6\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.1.6\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\s28297\CLionProjects\20180904Lab1Robot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\s28297\CLionProjects\20180904Lab1Robot\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/20180904Lab1Robot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/20180904Lab1Robot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/20180904Lab1Robot.dir/flags.make

CMakeFiles/20180904Lab1Robot.dir/main.c.obj: CMakeFiles/20180904Lab1Robot.dir/flags.make
CMakeFiles/20180904Lab1Robot.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\s28297\CLionProjects\20180904Lab1Robot\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/20180904Lab1Robot.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\20180904Lab1Robot.dir\main.c.obj   -c C:\Users\s28297\CLionProjects\20180904Lab1Robot\main.c

CMakeFiles/20180904Lab1Robot.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/20180904Lab1Robot.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\s28297\CLionProjects\20180904Lab1Robot\main.c > CMakeFiles\20180904Lab1Robot.dir\main.c.i

CMakeFiles/20180904Lab1Robot.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/20180904Lab1Robot.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\s28297\CLionProjects\20180904Lab1Robot\main.c -o CMakeFiles\20180904Lab1Robot.dir\main.c.s

CMakeFiles/20180904Lab1Robot.dir/main.c.obj.requires:

.PHONY : CMakeFiles/20180904Lab1Robot.dir/main.c.obj.requires

CMakeFiles/20180904Lab1Robot.dir/main.c.obj.provides: CMakeFiles/20180904Lab1Robot.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\20180904Lab1Robot.dir\build.make CMakeFiles/20180904Lab1Robot.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/20180904Lab1Robot.dir/main.c.obj.provides

CMakeFiles/20180904Lab1Robot.dir/main.c.obj.provides.build: CMakeFiles/20180904Lab1Robot.dir/main.c.obj


# Object files for target 20180904Lab1Robot
20180904Lab1Robot_OBJECTS = \
"CMakeFiles/20180904Lab1Robot.dir/main.c.obj"

# External object files for target 20180904Lab1Robot
20180904Lab1Robot_EXTERNAL_OBJECTS =

20180904Lab1Robot.exe: CMakeFiles/20180904Lab1Robot.dir/main.c.obj
20180904Lab1Robot.exe: CMakeFiles/20180904Lab1Robot.dir/build.make
20180904Lab1Robot.exe: CMakeFiles/20180904Lab1Robot.dir/linklibs.rsp
20180904Lab1Robot.exe: CMakeFiles/20180904Lab1Robot.dir/objects1.rsp
20180904Lab1Robot.exe: CMakeFiles/20180904Lab1Robot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\s28297\CLionProjects\20180904Lab1Robot\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 20180904Lab1Robot.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\20180904Lab1Robot.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/20180904Lab1Robot.dir/build: 20180904Lab1Robot.exe

.PHONY : CMakeFiles/20180904Lab1Robot.dir/build

CMakeFiles/20180904Lab1Robot.dir/requires: CMakeFiles/20180904Lab1Robot.dir/main.c.obj.requires

.PHONY : CMakeFiles/20180904Lab1Robot.dir/requires

CMakeFiles/20180904Lab1Robot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\20180904Lab1Robot.dir\cmake_clean.cmake
.PHONY : CMakeFiles/20180904Lab1Robot.dir/clean

CMakeFiles/20180904Lab1Robot.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\s28297\CLionProjects\20180904Lab1Robot C:\Users\s28297\CLionProjects\20180904Lab1Robot C:\Users\s28297\CLionProjects\20180904Lab1Robot\cmake-build-debug C:\Users\s28297\CLionProjects\20180904Lab1Robot\cmake-build-debug C:\Users\s28297\CLionProjects\20180904Lab1Robot\cmake-build-debug\CMakeFiles\20180904Lab1Robot.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/20180904Lab1Robot.dir/depend

