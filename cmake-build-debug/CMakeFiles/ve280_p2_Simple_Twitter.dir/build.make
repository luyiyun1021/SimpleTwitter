# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /home/lyy/.local/share/JetBrains/Toolbox/apps/CLion/ch-1/201.7223.86/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/lyy/.local/share/JetBrains/Toolbox/apps/CLion/ch-1/201.7223.86/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lyy/Ve280/project/ve280-p2-Simple-Twitter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ve280_p2_Simple_Twitter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ve280_p2_Simple_Twitter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ve280_p2_Simple_Twitter.dir/flags.make

CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.o: CMakeFiles/ve280_p2_Simple_Twitter.dir/flags.make
CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.o: ../p2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lyy/Ve280/project/ve280-p2-Simple-Twitter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.o -c /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/p2.cpp

CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/p2.cpp > CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.i

CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/p2.cpp -o CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.s

CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.o: CMakeFiles/ve280_p2_Simple_Twitter.dir/flags.make
CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.o: ../simulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lyy/Ve280/project/ve280-p2-Simple-Twitter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.o -c /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/simulation.cpp

CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/simulation.cpp > CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.i

CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/simulation.cpp -o CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.s

# Object files for target ve280_p2_Simple_Twitter
ve280_p2_Simple_Twitter_OBJECTS = \
"CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.o" \
"CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.o"

# External object files for target ve280_p2_Simple_Twitter
ve280_p2_Simple_Twitter_EXTERNAL_OBJECTS =

ve280_p2_Simple_Twitter: CMakeFiles/ve280_p2_Simple_Twitter.dir/p2.cpp.o
ve280_p2_Simple_Twitter: CMakeFiles/ve280_p2_Simple_Twitter.dir/simulation.cpp.o
ve280_p2_Simple_Twitter: CMakeFiles/ve280_p2_Simple_Twitter.dir/build.make
ve280_p2_Simple_Twitter: CMakeFiles/ve280_p2_Simple_Twitter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lyy/Ve280/project/ve280-p2-Simple-Twitter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ve280_p2_Simple_Twitter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ve280_p2_Simple_Twitter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ve280_p2_Simple_Twitter.dir/build: ve280_p2_Simple_Twitter

.PHONY : CMakeFiles/ve280_p2_Simple_Twitter.dir/build

CMakeFiles/ve280_p2_Simple_Twitter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ve280_p2_Simple_Twitter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ve280_p2_Simple_Twitter.dir/clean

CMakeFiles/ve280_p2_Simple_Twitter.dir/depend:
	cd /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lyy/Ve280/project/ve280-p2-Simple-Twitter /home/lyy/Ve280/project/ve280-p2-Simple-Twitter /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/cmake-build-debug /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/cmake-build-debug /home/lyy/Ve280/project/ve280-p2-Simple-Twitter/cmake-build-debug/CMakeFiles/ve280_p2_Simple_Twitter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ve280_p2_Simple_Twitter.dir/depend

