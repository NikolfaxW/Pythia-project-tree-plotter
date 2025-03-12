cmake_minimum_required(VERSION 3.10)
project(Pythia-project-tree-plotter)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Use root-config to get ROOT configuration
execute_process(COMMAND /home/nikolfax/opt/root/bin/root-config --cflags
        OUTPUT_VARIABLE ROOT_CFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND /home/nikolfax/opt/root/bin/root-config --libs
        OUTPUT_VARIABLE ROOT_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE)

# Extract include directories from ROOT_CFLAGS
string(REGEX MATCHALL "-I[^ ]+" ROOT_INCLUDES "${ROOT_CFLAGS}")
string(REGEX REPLACE "-I" "" ROOT_INCLUDES "${ROOT_INCLUDES}")

# Include directories
include_directories(
        ${ROOT_INCLUDES} # ROOT include directories from root-config
)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CFLAGS} -O2 -pedantic -W -Wall -Wshadow -fPIC -pthread")

# Add executable
add_executable(Pythia-project-tree-plotter main.cpp
                func.h
                func.cpp)

# Convert ROOT_LIBS string to a list of libraries
separate_arguments(ROOT_LIB_LIST UNIX_COMMAND "${ROOT_LIBS}")

# Link the necessary libraries
target_link_libraries(Pythia-project-tree-plotter PRIVATE
        ${ROOT_LIB_LIST} # Link ROOT libraries
)


