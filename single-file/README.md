# Single-File SmartStudent System

This is a single-file version of the SmartStudent System that combines all the data structures and functionality into one comprehensive C++ file.

## Features

This single-file program implements all 7 data structures:

1. **Linked List** - Student management
2. **Queue** - Service queue system
3. **Stack** - Transaction history with undo functionality
4. **Hash Table** - Fast student lookup
5. **Binary Search Tree (BST)** - Student scores management
6. **Graph** - Program study relationships
7. **Sorting & Searching** - Student data sorting and searching algorithms

## File Structure

- `main.cpp` - Single file containing all classes and functionality
- `build.bat` - Windows build script
- `build.sh` - Linux/Mac build script
- `run.bat` - Windows run script
- `run.sh` - Linux/Mac run script

## How to Build and Run

### Windows

1. **Build the program:**

   ```cmd
   build.bat
   ```

2. **Run the program:**
   ```cmd
   run.bat
   ```

### Linux/Mac

1. **Make scripts executable:**

   ```bash
   chmod +x build.sh run.sh
   ```

2. **Build the program:**

   ```bash
   ./build.sh
   ```

3. **Run the program:**
   ```bash
   ./run.sh
   ```

### Manual Compilation

**Windows:**

```cmd
g++ -std=c++11 -Wall -Wextra -o SmartStudent-SingleFile.exe main.cpp
```

**Linux/Mac:**

```bash
g++ -std=c++11 -Wall -Wextra -o SmartStudent-SingleFile main.cpp
```

## Advantages of Single-File Version

1. **Simplicity** - Everything in one file, easy to distribute
2. **Portability** - Just one file to copy and compile
3. **No Dependencies** - No need to manage multiple header files
4. **Self-contained** - All functionality in one place
5. **Easy to Submit** - Perfect for assignments or competitions

## Functionality

The program provides an interactive menu system with arrow key navigation and includes:

- **Student Management** using Linked List
- **Service Queue** for managing student services
- **Transaction Stack** with undo functionality
- **Hash Table** for fast student lookup
- **BST** for managing student scores
- **Graph** for program study relationships
- **Sorting & Searching** algorithms

## Cross-Platform Compatibility

The program works on both Windows and Linux/Mac systems with appropriate handling for:

- Screen clearing (`cls` vs `clear`)
- Keyboard input (`_getch()` vs `termios`)
- Arrow key codes (Windows vs Linux)

## Requirements

- C++ compiler with C++11 support or later
- Windows: MinGW, Visual Studio, or similar
- Linux/Mac: g++ compiler

## Usage

1. Compile the program using the provided build scripts
2. Run the executable
3. Use arrow keys to navigate the menu
4. Press Enter to select options
5. Follow the prompts for data input
6. Type 'cancel' to cancel input operations

The single-file version maintains all the functionality of the modular version while being contained in a single, easy-to-manage file.
