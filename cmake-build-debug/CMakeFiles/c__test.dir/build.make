# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Program Files\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Program Files\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\project\c-_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\project\c-_test\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/c__test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/c__test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/c__test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/c__test.dir/flags.make

CMakeFiles/c__test.dir/main.cpp.obj: CMakeFiles/c__test.dir/flags.make
CMakeFiles/c__test.dir/main.cpp.obj: E:/project/c-_test/main.cpp
CMakeFiles/c__test.dir/main.cpp.obj: CMakeFiles/c__test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\project\c-_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/c__test.dir/main.cpp.obj"
	E:\PROGRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/c__test.dir/main.cpp.obj -MF CMakeFiles\c__test.dir\main.cpp.obj.d -o CMakeFiles\c__test.dir\main.cpp.obj -c E:\project\c-_test\main.cpp

CMakeFiles/c__test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/c__test.dir/main.cpp.i"
	E:\PROGRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\project\c-_test\main.cpp > CMakeFiles\c__test.dir\main.cpp.i

CMakeFiles/c__test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/c__test.dir/main.cpp.s"
	E:\PROGRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\project\c-_test\main.cpp -o CMakeFiles\c__test.dir\main.cpp.s

CMakeFiles/c__test.dir/Account.cpp.obj: CMakeFiles/c__test.dir/flags.make
CMakeFiles/c__test.dir/Account.cpp.obj: E:/project/c-_test/Account.cpp
CMakeFiles/c__test.dir/Account.cpp.obj: CMakeFiles/c__test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\project\c-_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/c__test.dir/Account.cpp.obj"
	E:\PROGRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/c__test.dir/Account.cpp.obj -MF CMakeFiles\c__test.dir\Account.cpp.obj.d -o CMakeFiles\c__test.dir\Account.cpp.obj -c E:\project\c-_test\Account.cpp

CMakeFiles/c__test.dir/Account.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/c__test.dir/Account.cpp.i"
	E:\PROGRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\project\c-_test\Account.cpp > CMakeFiles\c__test.dir\Account.cpp.i

CMakeFiles/c__test.dir/Account.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/c__test.dir/Account.cpp.s"
	E:\PROGRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\project\c-_test\Account.cpp -o CMakeFiles\c__test.dir\Account.cpp.s

# Object files for target c__test
c__test_OBJECTS = \
"CMakeFiles/c__test.dir/main.cpp.obj" \
"CMakeFiles/c__test.dir/Account.cpp.obj"

# External object files for target c__test
c__test_EXTERNAL_OBJECTS =

c__test.exe: CMakeFiles/c__test.dir/main.cpp.obj
c__test.exe: CMakeFiles/c__test.dir/Account.cpp.obj
c__test.exe: CMakeFiles/c__test.dir/build.make
c__test.exe: CMakeFiles/c__test.dir/linkLibs.rsp
c__test.exe: CMakeFiles/c__test.dir/objects1.rsp
c__test.exe: CMakeFiles/c__test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=E:\project\c-_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable c__test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\c__test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/c__test.dir/build: c__test.exe
.PHONY : CMakeFiles/c__test.dir/build

CMakeFiles/c__test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\c__test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/c__test.dir/clean

CMakeFiles/c__test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\project\c-_test E:\project\c-_test E:\project\c-_test\cmake-build-debug E:\project\c-_test\cmake-build-debug E:\project\c-_test\cmake-build-debug\CMakeFiles\c__test.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/c__test.dir/depend

