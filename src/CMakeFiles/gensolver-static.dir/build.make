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
CMAKE_SOURCE_DIR = /home/miho/EigeneApps/gensolver/inst

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/miho/EigeneApps/gensolver/inst

# Include any dependencies generated for this target.
include src/CMakeFiles/gensolver-static.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/gensolver-static.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/gensolver-static.dir/flags.make

src/CMakeFiles/gensolver-static.dir/libgensolver.o: src/CMakeFiles/gensolver-static.dir/flags.make
src/CMakeFiles/gensolver-static.dir/libgensolver.o: src/libgensolver.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/miho/EigeneApps/gensolver/inst/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/gensolver-static.dir/libgensolver.o"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gensolver-static.dir/libgensolver.o -c /home/miho/EigeneApps/gensolver/inst/src/libgensolver.cpp

src/CMakeFiles/gensolver-static.dir/libgensolver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gensolver-static.dir/libgensolver.i"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/miho/EigeneApps/gensolver/inst/src/libgensolver.cpp > CMakeFiles/gensolver-static.dir/libgensolver.i

src/CMakeFiles/gensolver-static.dir/libgensolver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gensolver-static.dir/libgensolver.s"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/miho/EigeneApps/gensolver/inst/src/libgensolver.cpp -o CMakeFiles/gensolver-static.dir/libgensolver.s

src/CMakeFiles/gensolver-static.dir/libgensolver.o.requires:
.PHONY : src/CMakeFiles/gensolver-static.dir/libgensolver.o.requires

src/CMakeFiles/gensolver-static.dir/libgensolver.o.provides: src/CMakeFiles/gensolver-static.dir/libgensolver.o.requires
	$(MAKE) -f src/CMakeFiles/gensolver-static.dir/build.make src/CMakeFiles/gensolver-static.dir/libgensolver.o.provides.build
.PHONY : src/CMakeFiles/gensolver-static.dir/libgensolver.o.provides

src/CMakeFiles/gensolver-static.dir/libgensolver.o.provides.build: src/CMakeFiles/gensolver-static.dir/libgensolver.o
.PHONY : src/CMakeFiles/gensolver-static.dir/libgensolver.o.provides.build

src/CMakeFiles/gensolver-static.dir/libnnet.o: src/CMakeFiles/gensolver-static.dir/flags.make
src/CMakeFiles/gensolver-static.dir/libnnet.o: src/libnnet.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/miho/EigeneApps/gensolver/inst/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/gensolver-static.dir/libnnet.o"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gensolver-static.dir/libnnet.o -c /home/miho/EigeneApps/gensolver/inst/src/libnnet.cpp

src/CMakeFiles/gensolver-static.dir/libnnet.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gensolver-static.dir/libnnet.i"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/miho/EigeneApps/gensolver/inst/src/libnnet.cpp > CMakeFiles/gensolver-static.dir/libnnet.i

src/CMakeFiles/gensolver-static.dir/libnnet.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gensolver-static.dir/libnnet.s"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/miho/EigeneApps/gensolver/inst/src/libnnet.cpp -o CMakeFiles/gensolver-static.dir/libnnet.s

src/CMakeFiles/gensolver-static.dir/libnnet.o.requires:
.PHONY : src/CMakeFiles/gensolver-static.dir/libnnet.o.requires

src/CMakeFiles/gensolver-static.dir/libnnet.o.provides: src/CMakeFiles/gensolver-static.dir/libnnet.o.requires
	$(MAKE) -f src/CMakeFiles/gensolver-static.dir/build.make src/CMakeFiles/gensolver-static.dir/libnnet.o.provides.build
.PHONY : src/CMakeFiles/gensolver-static.dir/libnnet.o.provides

src/CMakeFiles/gensolver-static.dir/libnnet.o.provides.build: src/CMakeFiles/gensolver-static.dir/libnnet.o
.PHONY : src/CMakeFiles/gensolver-static.dir/libnnet.o.provides.build

src/CMakeFiles/gensolver-static.dir/librand.o: src/CMakeFiles/gensolver-static.dir/flags.make
src/CMakeFiles/gensolver-static.dir/librand.o: src/librand.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/miho/EigeneApps/gensolver/inst/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/gensolver-static.dir/librand.o"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gensolver-static.dir/librand.o -c /home/miho/EigeneApps/gensolver/inst/src/librand.cpp

src/CMakeFiles/gensolver-static.dir/librand.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gensolver-static.dir/librand.i"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/miho/EigeneApps/gensolver/inst/src/librand.cpp > CMakeFiles/gensolver-static.dir/librand.i

src/CMakeFiles/gensolver-static.dir/librand.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gensolver-static.dir/librand.s"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/miho/EigeneApps/gensolver/inst/src/librand.cpp -o CMakeFiles/gensolver-static.dir/librand.s

src/CMakeFiles/gensolver-static.dir/librand.o.requires:
.PHONY : src/CMakeFiles/gensolver-static.dir/librand.o.requires

src/CMakeFiles/gensolver-static.dir/librand.o.provides: src/CMakeFiles/gensolver-static.dir/librand.o.requires
	$(MAKE) -f src/CMakeFiles/gensolver-static.dir/build.make src/CMakeFiles/gensolver-static.dir/librand.o.provides.build
.PHONY : src/CMakeFiles/gensolver-static.dir/librand.o.provides

src/CMakeFiles/gensolver-static.dir/librand.o.provides.build: src/CMakeFiles/gensolver-static.dir/librand.o
.PHONY : src/CMakeFiles/gensolver-static.dir/librand.o.provides.build

src/CMakeFiles/gensolver-static.dir/libnetsolver.o: src/CMakeFiles/gensolver-static.dir/flags.make
src/CMakeFiles/gensolver-static.dir/libnetsolver.o: src/libnetsolver.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/miho/EigeneApps/gensolver/inst/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/gensolver-static.dir/libnetsolver.o"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gensolver-static.dir/libnetsolver.o -c /home/miho/EigeneApps/gensolver/inst/src/libnetsolver.cpp

src/CMakeFiles/gensolver-static.dir/libnetsolver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gensolver-static.dir/libnetsolver.i"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/miho/EigeneApps/gensolver/inst/src/libnetsolver.cpp > CMakeFiles/gensolver-static.dir/libnetsolver.i

src/CMakeFiles/gensolver-static.dir/libnetsolver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gensolver-static.dir/libnetsolver.s"
	cd /home/miho/EigeneApps/gensolver/inst/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/miho/EigeneApps/gensolver/inst/src/libnetsolver.cpp -o CMakeFiles/gensolver-static.dir/libnetsolver.s

src/CMakeFiles/gensolver-static.dir/libnetsolver.o.requires:
.PHONY : src/CMakeFiles/gensolver-static.dir/libnetsolver.o.requires

src/CMakeFiles/gensolver-static.dir/libnetsolver.o.provides: src/CMakeFiles/gensolver-static.dir/libnetsolver.o.requires
	$(MAKE) -f src/CMakeFiles/gensolver-static.dir/build.make src/CMakeFiles/gensolver-static.dir/libnetsolver.o.provides.build
.PHONY : src/CMakeFiles/gensolver-static.dir/libnetsolver.o.provides

src/CMakeFiles/gensolver-static.dir/libnetsolver.o.provides.build: src/CMakeFiles/gensolver-static.dir/libnetsolver.o
.PHONY : src/CMakeFiles/gensolver-static.dir/libnetsolver.o.provides.build

# Object files for target gensolver-static
gensolver__static_OBJECTS = \
"CMakeFiles/gensolver-static.dir/libgensolver.o" \
"CMakeFiles/gensolver-static.dir/libnnet.o" \
"CMakeFiles/gensolver-static.dir/librand.o" \
"CMakeFiles/gensolver-static.dir/libnetsolver.o"

# External object files for target gensolver-static
gensolver__static_EXTERNAL_OBJECTS =

src/libgensolver.a: src/CMakeFiles/gensolver-static.dir/libgensolver.o
src/libgensolver.a: src/CMakeFiles/gensolver-static.dir/libnnet.o
src/libgensolver.a: src/CMakeFiles/gensolver-static.dir/librand.o
src/libgensolver.a: src/CMakeFiles/gensolver-static.dir/libnetsolver.o
src/libgensolver.a: src/CMakeFiles/gensolver-static.dir/build.make
src/libgensolver.a: src/CMakeFiles/gensolver-static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libgensolver.a"
	cd /home/miho/EigeneApps/gensolver/inst/src && $(CMAKE_COMMAND) -P CMakeFiles/gensolver-static.dir/cmake_clean_target.cmake
	cd /home/miho/EigeneApps/gensolver/inst/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gensolver-static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/gensolver-static.dir/build: src/libgensolver.a
.PHONY : src/CMakeFiles/gensolver-static.dir/build

src/CMakeFiles/gensolver-static.dir/requires: src/CMakeFiles/gensolver-static.dir/libgensolver.o.requires
src/CMakeFiles/gensolver-static.dir/requires: src/CMakeFiles/gensolver-static.dir/libnnet.o.requires
src/CMakeFiles/gensolver-static.dir/requires: src/CMakeFiles/gensolver-static.dir/librand.o.requires
src/CMakeFiles/gensolver-static.dir/requires: src/CMakeFiles/gensolver-static.dir/libnetsolver.o.requires
.PHONY : src/CMakeFiles/gensolver-static.dir/requires

src/CMakeFiles/gensolver-static.dir/clean:
	cd /home/miho/EigeneApps/gensolver/inst/src && $(CMAKE_COMMAND) -P CMakeFiles/gensolver-static.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/gensolver-static.dir/clean

src/CMakeFiles/gensolver-static.dir/depend:
	cd /home/miho/EigeneApps/gensolver/inst && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/miho/EigeneApps/gensolver/inst /home/miho/EigeneApps/gensolver/inst/src /home/miho/EigeneApps/gensolver/inst /home/miho/EigeneApps/gensolver/inst/src /home/miho/EigeneApps/gensolver/inst/src/CMakeFiles/gensolver-static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/gensolver-static.dir/depend
