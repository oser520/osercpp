# file: makefile
# author: Omar A Serrano 
# date: 2016-03-22
#
# makefile for building unit tests.

SHELL = /bin/sh

# Source and include directories.
VPATH = .:../
INCDIR = -I../

# Include directory for googletest.
GTFLAGS = -isystem $(GTEST_DIR)/include

# Paths for libraries, and libraries used.
LDFLAGS  = -L/opt/googletest
LFLAGS   = -lgtest -lpthread

# Compiler flags.
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
CXXFLAGS += $(GTFLAGS) $(INCDIR)

# Dependencies for each unit test program.
OBJ_QUEUE = test_queue.o

# Combine unique object files.
OBJ_LIST := $(sort $(OBJ_QUEUE))

# Unit test programs.
TARGETS = test_queue

all: $(TARGETS)

test_queue: $(OBJ_QUEUE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LFLAGS) -o $@

# Header dependencies.
$(OBJ_QUEUE): queue.hh

.PHONY: run clean
# Run all unit tests.
run: $(TARGETS)
	-@./runtest.py $^

clean:
	$(RM) $(OBJ_LIST) $(TARGETS) 2>/dev/null
