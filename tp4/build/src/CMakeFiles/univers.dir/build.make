# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build

# Include any dependencies generated for this target.
include src/CMakeFiles/univers.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/univers.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/univers.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/univers.dir/flags.make

src/CMakeFiles/univers.dir/univers.cxx.o: src/CMakeFiles/univers.dir/flags.make
src/CMakeFiles/univers.dir/univers.cxx.o: /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/src/univers.cxx
src/CMakeFiles/univers.dir/univers.cxx.o: src/CMakeFiles/univers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/univers.dir/univers.cxx.o"
	cd /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/univers.dir/univers.cxx.o -MF CMakeFiles/univers.dir/univers.cxx.o.d -o CMakeFiles/univers.dir/univers.cxx.o -c /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/src/univers.cxx

src/CMakeFiles/univers.dir/univers.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/univers.dir/univers.cxx.i"
	cd /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/src/univers.cxx > CMakeFiles/univers.dir/univers.cxx.i

src/CMakeFiles/univers.dir/univers.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/univers.dir/univers.cxx.s"
	cd /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/src/univers.cxx -o CMakeFiles/univers.dir/univers.cxx.s

# Object files for target univers
univers_OBJECTS = \
"CMakeFiles/univers.dir/univers.cxx.o"

# External object files for target univers
univers_EXTERNAL_OBJECTS =

src/libunivers.a: src/CMakeFiles/univers.dir/univers.cxx.o
src/libunivers.a: src/CMakeFiles/univers.dir/build.make
src/libunivers.a: src/CMakeFiles/univers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libunivers.a"
	cd /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/src && $(CMAKE_COMMAND) -P CMakeFiles/univers.dir/cmake_clean_target.cmake
	cd /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/univers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/univers.dir/build: src/libunivers.a
.PHONY : src/CMakeFiles/univers.dir/build

src/CMakeFiles/univers.dir/clean:
	cd /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/src && $(CMAKE_COMMAND) -P CMakeFiles/univers.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/univers.dir/clean

src/CMakeFiles/univers.dir/depend:
	cd /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/src /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/src /home/samy/cplusplus/tp3/cppma-spring2025-lab3-infra/Lab3-Infra/build/src/CMakeFiles/univers.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/univers.dir/depend

