# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build

# Include any dependencies generated for this target.
include CMakeFiles/CGRA_Simulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CGRA_Simulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CGRA_Simulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CGRA_Simulator.dir/flags.make

CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.o: ../src/CGRAsim.cc
CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/CGRAsim.cc

CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/CGRAsim.cc > CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.i

CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/CGRAsim.cc -o CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.s

CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.o: ../src/DebugSupport.cc
CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/DebugSupport.cc

CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/DebugSupport.cc > CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.i

CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/DebugSupport.cc -o CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.s

CMakeFiles/CGRA_Simulator.dir/src/GR.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/GR.cc.o: ../src/GR.cc
CMakeFiles/CGRA_Simulator.dir/src/GR.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/GR.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/GR.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/GR.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/GR.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/GR.cc

CMakeFiles/CGRA_Simulator.dir/src/GR.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/GR.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/GR.cc > CMakeFiles/CGRA_Simulator.dir/src/GR.cc.i

CMakeFiles/CGRA_Simulator.dir/src/GR.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/GR.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/GR.cc -o CMakeFiles/CGRA_Simulator.dir/src/GR.cc.s

CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.o: ../src/Instrction_decoder.cc
CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/Instrction_decoder.cc

CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/Instrction_decoder.cc > CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.i

CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/Instrction_decoder.cc -o CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.s

CMakeFiles/CGRA_Simulator.dir/src/PE.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/PE.cc.o: ../src/PE.cc
CMakeFiles/CGRA_Simulator.dir/src/PE.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/PE.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/PE.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/PE.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/PE.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/PE.cc

CMakeFiles/CGRA_Simulator.dir/src/PE.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/PE.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/PE.cc > CMakeFiles/CGRA_Simulator.dir/src/PE.cc.i

CMakeFiles/CGRA_Simulator.dir/src/PE.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/PE.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/PE.cc -o CMakeFiles/CGRA_Simulator.dir/src/PE.cc.s

CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.o: ../src/PEA.cc
CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/PEA.cc

CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/PEA.cc > CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.i

CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/PEA.cc -o CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.s

CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.o: ../src/WIRE.cc
CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/WIRE.cc

CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/WIRE.cc > CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.i

CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/WIRE.cc -o CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.s

CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.o: ../src/alg0.cc
CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg0.cc

CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg0.cc > CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.i

CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg0.cc -o CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.s

CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.o: ../src/alg1.cc
CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg1.cc

CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg1.cc > CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.i

CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg1.cc -o CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.s

CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.o: ../src/alg2.cc
CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg2.cc

CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg2.cc > CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.i

CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg2.cc -o CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.s

CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.o: ../src/alg3.cc
CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg3.cc

CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg3.cc > CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.i

CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg3.cc -o CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.s

CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.o: ../src/alg4.cc
CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg4.cc

CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg4.cc > CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.i

CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg4.cc -o CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.s

CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.o: ../src/alg5.cc
CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg5.cc

CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg5.cc > CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.i

CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg5.cc -o CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.s

CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.o: ../src/alg6.cc
CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg6.cc

CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg6.cc > CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.i

CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg6.cc -o CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.s

CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.o: CMakeFiles/CGRA_Simulator.dir/flags.make
CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.o: ../src/alg7.cc
CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.o: CMakeFiles/CGRA_Simulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.o -MF CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.o.d -o CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.o -c /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg7.cc

CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg7.cc > CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.i

CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/src/alg7.cc -o CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.s

# Object files for target CGRA_Simulator
CGRA_Simulator_OBJECTS = \
"CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/GR.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/PE.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.o" \
"CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.o"

# External object files for target CGRA_Simulator
CGRA_Simulator_EXTERNAL_OBJECTS =

CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/CGRAsim.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/DebugSupport.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/GR.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/Instrction_decoder.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/PE.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/PEA.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/WIRE.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/alg0.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/alg1.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/alg2.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/alg3.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/alg4.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/alg5.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/alg6.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/src/alg7.cc.o
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/build.make
CGRA_Simulator: ../lib/libCGRANLParam_BF.a
CGRA_Simulator: ../lib/libCGRALSU.a
CGRA_Simulator: CMakeFiles/CGRA_Simulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable CGRA_Simulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CGRA_Simulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CGRA_Simulator.dir/build: CGRA_Simulator
.PHONY : CMakeFiles/CGRA_Simulator.dir/build

CMakeFiles/CGRA_Simulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CGRA_Simulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CGRA_Simulator.dir/clean

CMakeFiles/CGRA_Simulator.dir/depend:
	cd /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build /home/dkx/Downloads/CGRA_ToolChain_1103_未封装有PEcc/CGRA_ToolChain_1103/CGRA_Simulator/build/CMakeFiles/CGRA_Simulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CGRA_Simulator.dir/depend

