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
include src/CMakeFiles/grabidentifiers.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/grabidentifiers.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/grabidentifiers.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/grabidentifiers.dir/flags.make

src/CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.o: src/CMakeFiles/grabidentifiers.dir/flags.make
src/CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.o: /Users/tarunmittal/Desktop/NLP\ Project/ensemble_tagger/src/GetWordsFromArchive.cpp
src/CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.o: src/CMakeFiles/grabidentifiers.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.o"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/src" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.o -MF CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.o.d -o CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.o -c "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/src/GetWordsFromArchive.cpp"

src/CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.i"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/src" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/src/GetWordsFromArchive.cpp" > CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.i

src/CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.s"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/src" && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/src/GetWordsFromArchive.cpp" -o CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.s

# Object files for target grabidentifiers
grabidentifiers_OBJECTS = \
"CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.o"

# External object files for target grabidentifiers
grabidentifiers_EXTERNAL_OBJECTS =

bin/grabidentifiers: src/CMakeFiles/grabidentifiers.dir/GetWordsFromArchive.cpp.o
bin/grabidentifiers: src/CMakeFiles/grabidentifiers.dir/build.make
bin/grabidentifiers: bin/libsrcsaxeventdispatch.a
bin/grabidentifiers: bin/libsrcsax.a
bin/grabidentifiers: /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libxml2.tbd
bin/grabidentifiers: /Library/Frameworks/Python.framework/Versions/3.11/lib/libpython3.11.dylib
bin/grabidentifiers: src/CMakeFiles/grabidentifiers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/grabidentifiers"
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/grabidentifiers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/grabidentifiers.dir/build: bin/grabidentifiers
.PHONY : src/CMakeFiles/grabidentifiers.dir/build

src/CMakeFiles/grabidentifiers.dir/clean:
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/grabidentifiers.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/grabidentifiers.dir/clean

src/CMakeFiles/grabidentifiers.dir/depend:
	cd "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/src" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/src" "/Users/tarunmittal/Desktop/NLP Project/ensemble_tagger/build/src/CMakeFiles/grabidentifiers.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/CMakeFiles/grabidentifiers.dir/depend

