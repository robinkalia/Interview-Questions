# Robin Kalia
# robinkalia@berkeley.edu
# UC Berkeley
#
# AiFi Full Stack Software Engineer Interview
# Makefile: Contains the instructions to make the AiFiMessager executable


CC = gcc
CXX = g++
EXEC = aifi


all : $(EXEC)
# Compilation flags:
# -O3   turns on optimization
# -g    enables debugging support
# -Wall turns on all compiler warnings
CXXFLAGS = -O3 -g -std=c++11 -Wall

# Linking flags: Link to the static and run-time libraries
LFLAGS = -lm

# Object files: List of object files needed to build the program.
OBJECTS = Streamer.o Synchronizer.o AiFiMessager.o main.o

SRC = Streamer.cpp Synchronizer.cpp AiFiMessager.cpp main.cpp

# Linking rule:
$(EXEC): $(OBJECTS)
	$(CXX) -c $(CXXFLAGS) $(SRC)
	$(CXX) $^ $(LFLAGS) -o $@


# Clean-up rule:
clean:
	rm -f $(EXEC) *.o *~