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
include srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/compiler_depend.make

# Include the progress variables for this target.
include srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/progress.make

# Include the compile flags for this target's objects.
include srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/flags.make

srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.o: srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/flags.make
srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.o: /Users/tarunmittal/Desktop/NLP\ Project/ensemble_tagger/srcSAXEventDispatch/tests/TestFnSignaturePolicy.cpp
srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.o: srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.o"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.o -MF CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.o.d -o CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.o -c "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/srcSAXEventDispatch/tests/TestFnSignaturePolicy.cpp"

srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.i"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/srcSAXEventDispatch/tests/TestFnSignaturePolicy.cpp" > CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.i

srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.s"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/srcSAXEventDispatch/tests/TestFnSignaturePolicy.cpp" -o CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.s

# Object files for target TestFnSignaturePolicy
TestFnSignaturePolicy_OBJECTS = \
"CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.o"

# External object files for target TestFnSignaturePolicy
TestFnSignaturePolicy_EXTERNAL_OBJECTS =

bin/TestFnSignaturePolicy: srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/TestFnSignaturePolicy.cpp.o
bin/TestFnSignaturePolicy: srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/build.make
bin/TestFnSignaturePolicy: bin/libsrcsaxeventdispatch.a
bin/TestFnSignaturePolicy: bin/libsrcsax.a
bin/TestFnSignaturePolicy: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libxml2.tbd
bin/TestFnSignaturePolicy: srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/TestFnSignaturePolicy"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestFnSignaturePolicy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/build: bin/TestFnSignaturePolicy
.PHONY : srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/build

srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/clean:
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" && $(CMAKE_COMMAND) -P CMakeFiles/TestFnSignaturePolicy.dir/cmake_clean.cmake
.PHONY : srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/clean

srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/depend:
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/srcSAXEventDispatch/tests" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : srcSAXEventDispatch/tests/CMakeFiles/TestFnSignaturePolicy.dir/depend

