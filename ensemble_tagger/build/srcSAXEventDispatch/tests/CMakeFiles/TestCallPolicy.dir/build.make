# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.26.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build"

# Include any dependencies generated for this target.
include srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/compiler_depend.make

# Include the progress variables for this target.
include srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/progress.make

# Include the compile flags for this target's objects.
include srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/flags.make

srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.o: srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/flags.make
srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.o: /Users/tarunmittal/Desktop/NLP\ Project/ensemble_tagger/srcSAXEventDispatch/tests/TestCallPolicy.cpp
srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.o: srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.o"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.o -MF CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.o.d -o CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.o -c "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/srcSAXEventDispatch/tests/TestCallPolicy.cpp"

srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.i"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/srcSAXEventDispatch/tests/TestCallPolicy.cpp" > CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.i

srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.s"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/srcSAXEventDispatch/tests/TestCallPolicy.cpp" -o CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.s

# Object files for target TestCallPolicy
TestCallPolicy_OBJECTS = \
"CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.o"

# External object files for target TestCallPolicy
TestCallPolicy_EXTERNAL_OBJECTS =

bin/TestCallPolicy: srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/TestCallPolicy.cpp.o
bin/TestCallPolicy: srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/build.make
bin/TestCallPolicy: bin/libsrcsaxeventdispatch.a
bin/TestCallPolicy: bin/libsrcsax.a
bin/TestCallPolicy: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libxml2.tbd
bin/TestCallPolicy: srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/TestCallPolicy"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestCallPolicy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/build: bin/TestCallPolicy
.PHONY : srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/build

srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/clean:
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && $(CMAKE_COMMAND) -P CMakeFiles/TestCallPolicy.dir/cmake_clean.cmake
.PHONY : srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/clean

srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/depend:
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/srcSAXEventDispatch/tests" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : srcSAXEventDispatch/tests/CMakeFiles/TestCallPolicy.dir/depend

