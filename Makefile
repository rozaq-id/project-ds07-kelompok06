# Makefile untuk SmartStudent System
# Cross-platform Makefile

# Detect platform
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    TARGET = SmartStudent.exe
    CLEAN_CMD = del /f *.o $(TARGET) 2>nul || echo "Clean completed"
    RUN_CMD = $(TARGET)
else
    DETECTED_OS := $(shell uname -s)
    TARGET = SmartStudent
    CLEAN_CMD = rm -f *.o $(TARGET)
    RUN_CMD = ./$(TARGET)
endif

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SOURCES = main.cpp StudentList.cpp ServiceQueue.cpp TransactionStack.cpp StudentHashTable.cpp BST.cpp ProdiGraph.cpp StudentSorter.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)
	@echo "Build completed for $(DETECTED_OS)"

# Kompilasi program
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Kompilasi object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up (cross-platform)
clean:
	$(CLEAN_CMD)

# Run program (cross-platform)
run: $(TARGET)
	$(RUN_CMD)

# Windows specific targets
win-build:
	$(MAKE) CXX=g++ TARGET=SmartStudent.exe

# Linux specific targets  
linux-build:
	$(MAKE) CXX=g++ TARGET=SmartStudent

.PHONY: all clean run win-build linux-build
