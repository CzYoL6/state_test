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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/e/Programming/state_test/server/server_ShooterTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/Programming/state_test/server/server_ShooterTest/Build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/Source/Player.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/Player.cpp.o: ../Source/Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/Source/Player.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/Player.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/Player.cpp

CMakeFiles/server.dir/Source/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/Player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/Player.cpp > CMakeFiles/server.dir/Source/Player.cpp.i

CMakeFiles/server.dir/Source/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/Player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/Player.cpp -o CMakeFiles/server.dir/Source/Player.cpp.s

CMakeFiles/server.dir/Source/PlayerMovement.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/PlayerMovement.cpp.o: ../Source/PlayerMovement.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/Source/PlayerMovement.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/PlayerMovement.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/PlayerMovement.cpp

CMakeFiles/server.dir/Source/PlayerMovement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/PlayerMovement.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/PlayerMovement.cpp > CMakeFiles/server.dir/Source/PlayerMovement.cpp.i

CMakeFiles/server.dir/Source/PlayerMovement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/PlayerMovement.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/PlayerMovement.cpp -o CMakeFiles/server.dir/Source/PlayerMovement.cpp.s

CMakeFiles/server.dir/Source/client.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/client.cpp.o: ../Source/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/Source/client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/client.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/client.cpp

CMakeFiles/server.dir/Source/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/client.cpp > CMakeFiles/server.dir/Source/client.cpp.i

CMakeFiles/server.dir/Source/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/client.cpp -o CMakeFiles/server.dir/Source/client.cpp.s

CMakeFiles/server.dir/Source/game.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/game.cpp.o: ../Source/game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/Source/game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/game.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/game.cpp

CMakeFiles/server.dir/Source/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/game.cpp > CMakeFiles/server.dir/Source/game.cpp.i

CMakeFiles/server.dir/Source/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/game.cpp -o CMakeFiles/server.dir/Source/game.cpp.s

CMakeFiles/server.dir/Source/ikcp.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/ikcp.c.o: ../Source/ikcp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/server.dir/Source/ikcp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/Source/ikcp.c.o   -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/ikcp.c

CMakeFiles/server.dir/Source/ikcp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/Source/ikcp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/ikcp.c > CMakeFiles/server.dir/Source/ikcp.c.i

CMakeFiles/server.dir/Source/ikcp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/Source/ikcp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/ikcp.c -o CMakeFiles/server.dir/Source/ikcp.c.s

CMakeFiles/server.dir/Source/kcpserver.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/kcpserver.cpp.o: ../Source/kcpserver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/Source/kcpserver.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/kcpserver.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/kcpserver.cpp

CMakeFiles/server.dir/Source/kcpserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/kcpserver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/kcpserver.cpp > CMakeFiles/server.dir/Source/kcpserver.cpp.i

CMakeFiles/server.dir/Source/kcpserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/kcpserver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/kcpserver.cpp -o CMakeFiles/server.dir/Source/kcpserver.cpp.s

CMakeFiles/server.dir/Source/kcpsession.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/kcpsession.cpp.o: ../Source/kcpsession.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/Source/kcpsession.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/kcpsession.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/kcpsession.cpp

CMakeFiles/server.dir/Source/kcpsession.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/kcpsession.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/kcpsession.cpp > CMakeFiles/server.dir/Source/kcpsession.cpp.i

CMakeFiles/server.dir/Source/kcpsession.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/kcpsession.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/kcpsession.cpp -o CMakeFiles/server.dir/Source/kcpsession.cpp.s

CMakeFiles/server.dir/Source/message.pb.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/message.pb.cc.o: ../Source/message.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/server.dir/Source/message.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/message.pb.cc.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/message.pb.cc

CMakeFiles/server.dir/Source/message.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/message.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/message.pb.cc > CMakeFiles/server.dir/Source/message.pb.cc.i

CMakeFiles/server.dir/Source/message.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/message.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/message.pb.cc -o CMakeFiles/server.dir/Source/message.pb.cc.s

CMakeFiles/server.dir/Source/packet.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/packet.cpp.o: ../Source/packet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/server.dir/Source/packet.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/packet.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/packet.cpp

CMakeFiles/server.dir/Source/packet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/packet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/packet.cpp > CMakeFiles/server.dir/Source/packet.cpp.i

CMakeFiles/server.dir/Source/packet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/packet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/packet.cpp -o CMakeFiles/server.dir/Source/packet.cpp.s

CMakeFiles/server.dir/Source/random_engine.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/random_engine.cpp.o: ../Source/random_engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/server.dir/Source/random_engine.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/random_engine.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/random_engine.cpp

CMakeFiles/server.dir/Source/random_engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/random_engine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/random_engine.cpp > CMakeFiles/server.dir/Source/random_engine.cpp.i

CMakeFiles/server.dir/Source/random_engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/random_engine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/random_engine.cpp -o CMakeFiles/server.dir/Source/random_engine.cpp.s

CMakeFiles/server.dir/Source/server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/server.cpp.o: ../Source/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/server.dir/Source/server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/server.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server.cpp

CMakeFiles/server.dir/Source/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server.cpp > CMakeFiles/server.dir/Source/server.cpp.i

CMakeFiles/server.dir/Source/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server.cpp -o CMakeFiles/server.dir/Source/server.cpp.s

CMakeFiles/server.dir/Source/server_handle.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/server_handle.cpp.o: ../Source/server_handle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/server.dir/Source/server_handle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/server_handle.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server_handle.cpp

CMakeFiles/server.dir/Source/server_handle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/server_handle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server_handle.cpp > CMakeFiles/server.dir/Source/server_handle.cpp.i

CMakeFiles/server.dir/Source/server_handle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/server_handle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server_handle.cpp -o CMakeFiles/server.dir/Source/server_handle.cpp.s

CMakeFiles/server.dir/Source/server_main.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/server_main.cpp.o: ../Source/server_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/server.dir/Source/server_main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/server_main.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server_main.cpp

CMakeFiles/server.dir/Source/server_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/server_main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server_main.cpp > CMakeFiles/server.dir/Source/server_main.cpp.i

CMakeFiles/server.dir/Source/server_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/server_main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server_main.cpp -o CMakeFiles/server.dir/Source/server_main.cpp.s

CMakeFiles/server.dir/Source/server_send.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Source/server_send.cpp.o: ../Source/server_send.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/server.dir/Source/server_send.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/Source/server_send.cpp.o -c /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server_send.cpp

CMakeFiles/server.dir/Source/server_send.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Source/server_send.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server_send.cpp > CMakeFiles/server.dir/Source/server_send.cpp.i

CMakeFiles/server.dir/Source/server_send.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Source/server_send.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/Programming/state_test/server/server_ShooterTest/Source/server_send.cpp -o CMakeFiles/server.dir/Source/server_send.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/Source/Player.cpp.o" \
"CMakeFiles/server.dir/Source/PlayerMovement.cpp.o" \
"CMakeFiles/server.dir/Source/client.cpp.o" \
"CMakeFiles/server.dir/Source/game.cpp.o" \
"CMakeFiles/server.dir/Source/ikcp.c.o" \
"CMakeFiles/server.dir/Source/kcpserver.cpp.o" \
"CMakeFiles/server.dir/Source/kcpsession.cpp.o" \
"CMakeFiles/server.dir/Source/message.pb.cc.o" \
"CMakeFiles/server.dir/Source/packet.cpp.o" \
"CMakeFiles/server.dir/Source/random_engine.cpp.o" \
"CMakeFiles/server.dir/Source/server.cpp.o" \
"CMakeFiles/server.dir/Source/server_handle.cpp.o" \
"CMakeFiles/server.dir/Source/server_main.cpp.o" \
"CMakeFiles/server.dir/Source/server_send.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/Source/Player.cpp.o
server: CMakeFiles/server.dir/Source/PlayerMovement.cpp.o
server: CMakeFiles/server.dir/Source/client.cpp.o
server: CMakeFiles/server.dir/Source/game.cpp.o
server: CMakeFiles/server.dir/Source/ikcp.c.o
server: CMakeFiles/server.dir/Source/kcpserver.cpp.o
server: CMakeFiles/server.dir/Source/kcpsession.cpp.o
server: CMakeFiles/server.dir/Source/message.pb.cc.o
server: CMakeFiles/server.dir/Source/packet.cpp.o
server: CMakeFiles/server.dir/Source/random_engine.cpp.o
server: CMakeFiles/server.dir/Source/server.cpp.o
server: CMakeFiles/server.dir/Source/server_handle.cpp.o
server: CMakeFiles/server.dir/Source/server_main.cpp.o
server: CMakeFiles/server.dir/Source/server_send.cpp.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /mnt/e/Programming/state_test/server/server_ShooterTest/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/Programming/state_test/server/server_ShooterTest /mnt/e/Programming/state_test/server/server_ShooterTest /mnt/e/Programming/state_test/server/server_ShooterTest/Build /mnt/e/Programming/state_test/server/server_ShooterTest/Build /mnt/e/Programming/state_test/server/server_ShooterTest/Build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

