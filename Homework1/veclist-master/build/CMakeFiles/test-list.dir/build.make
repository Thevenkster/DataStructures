# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master/build"

# Include any dependencies generated for this target.
include CMakeFiles/test-list.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test-list.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test-list.dir/flags.make

CMakeFiles/test-list.dir/list.cpp.o: CMakeFiles/test-list.dir/flags.make
CMakeFiles/test-list.dir/list.cpp.o: ../list.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test-list.dir/list.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-list.dir/list.cpp.o -c "/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master/list.cpp"

CMakeFiles/test-list.dir/list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-list.dir/list.cpp.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

CMakeFiles/test-list.dir/list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-list.dir/list.cpp.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

CMakeFiles/test-list.dir/list.cpp.o.requires:

.PHONY : CMakeFiles/test-list.dir/list.cpp.o.requires

CMakeFiles/test-list.dir/list.cpp.o.provides: CMakeFiles/test-list.dir/list.cpp.o.requires
	$(MAKE) -f CMakeFiles/test-list.dir/build.make CMakeFiles/test-list.dir/list.cpp.o.provides.build
.PHONY : CMakeFiles/test-list.dir/list.cpp.o.provides

CMakeFiles/test-list.dir/list.cpp.o.provides.build: CMakeFiles/test-list.dir/list.cpp.o


# Object files for target test-list
test__list_OBJECTS = \
"CMakeFiles/test-list.dir/list.cpp.o"

# External object files for target test-list
test__list_EXTERNAL_OBJECTS =

test-list: CMakeFiles/test-list.dir/list.cpp.o
test-list: CMakeFiles/test-list.dir/build.make
test-list: CMakeFiles/test-list.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test-list"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-list.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test-list.dir/build: test-list

.PHONY : CMakeFiles/test-list.dir/build

CMakeFiles/test-list.dir/requires: CMakeFiles/test-list.dir/list.cpp.o.requires

.PHONY : CMakeFiles/test-list.dir/requires

CMakeFiles/test-list.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test-list.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test-list.dir/clean

CMakeFiles/test-list.dir/depend:
	cd "/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master" "/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master" "/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master/build" "/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master/build" "/Users/karthikvenkat/Desktop/Programming/Data Structures/veclist-master/build/CMakeFiles/test-list.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/test-list.dir/depend

