# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/homework-1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/homework-1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/homework-1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/homework-1.dir/flags.make

CMakeFiles/homework-1.dir/src/main.cpp.o: CMakeFiles/homework-1.dir/flags.make
CMakeFiles/homework-1.dir/src/main.cpp.o: /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/main.cpp
CMakeFiles/homework-1.dir/src/main.cpp.o: CMakeFiles/homework-1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/homework-1.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/homework-1.dir/src/main.cpp.o -MF CMakeFiles/homework-1.dir/src/main.cpp.o.d -o CMakeFiles/homework-1.dir/src/main.cpp.o -c /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/main.cpp

CMakeFiles/homework-1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/homework-1.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/main.cpp > CMakeFiles/homework-1.dir/src/main.cpp.i

CMakeFiles/homework-1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/homework-1.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/main.cpp -o CMakeFiles/homework-1.dir/src/main.cpp.s

CMakeFiles/homework-1.dir/src/Zoo.cpp.o: CMakeFiles/homework-1.dir/flags.make
CMakeFiles/homework-1.dir/src/Zoo.cpp.o: /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/Zoo.cpp
CMakeFiles/homework-1.dir/src/Zoo.cpp.o: CMakeFiles/homework-1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/homework-1.dir/src/Zoo.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/homework-1.dir/src/Zoo.cpp.o -MF CMakeFiles/homework-1.dir/src/Zoo.cpp.o.d -o CMakeFiles/homework-1.dir/src/Zoo.cpp.o -c /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/Zoo.cpp

CMakeFiles/homework-1.dir/src/Zoo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/homework-1.dir/src/Zoo.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/Zoo.cpp > CMakeFiles/homework-1.dir/src/Zoo.cpp.i

CMakeFiles/homework-1.dir/src/Zoo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/homework-1.dir/src/Zoo.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/Zoo.cpp -o CMakeFiles/homework-1.dir/src/Zoo.cpp.s

CMakeFiles/homework-1.dir/src/ZooApp.cpp.o: CMakeFiles/homework-1.dir/flags.make
CMakeFiles/homework-1.dir/src/ZooApp.cpp.o: /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/ZooApp.cpp
CMakeFiles/homework-1.dir/src/ZooApp.cpp.o: CMakeFiles/homework-1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/homework-1.dir/src/ZooApp.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/homework-1.dir/src/ZooApp.cpp.o -MF CMakeFiles/homework-1.dir/src/ZooApp.cpp.o.d -o CMakeFiles/homework-1.dir/src/ZooApp.cpp.o -c /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/ZooApp.cpp

CMakeFiles/homework-1.dir/src/ZooApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/homework-1.dir/src/ZooApp.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/ZooApp.cpp > CMakeFiles/homework-1.dir/src/ZooApp.cpp.i

CMakeFiles/homework-1.dir/src/ZooApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/homework-1.dir/src/ZooApp.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/src/ZooApp.cpp -o CMakeFiles/homework-1.dir/src/ZooApp.cpp.s

# Object files for target homework-1
homework__1_OBJECTS = \
"CMakeFiles/homework-1.dir/src/main.cpp.o" \
"CMakeFiles/homework-1.dir/src/Zoo.cpp.o" \
"CMakeFiles/homework-1.dir/src/ZooApp.cpp.o"

# External object files for target homework-1
homework__1_EXTERNAL_OBJECTS =

homework-1: CMakeFiles/homework-1.dir/src/main.cpp.o
homework-1: CMakeFiles/homework-1.dir/src/Zoo.cpp.o
homework-1: CMakeFiles/homework-1.dir/src/ZooApp.cpp.o
homework-1: CMakeFiles/homework-1.dir/build.make
homework-1: CMakeFiles/homework-1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable homework-1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/homework-1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/homework-1.dir/build: homework-1
.PHONY : CMakeFiles/homework-1.dir/build

CMakeFiles/homework-1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/homework-1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/homework-1.dir/clean

CMakeFiles/homework-1.dir/depend:
	cd /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1 /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1 /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/cmake-build-debug /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/cmake-build-debug /Users/nazarzakrevskij/CLionProjects/SoftwareEngineering/homework-1/cmake-build-debug/CMakeFiles/homework-1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/homework-1.dir/depend

