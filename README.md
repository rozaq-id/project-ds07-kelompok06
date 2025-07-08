# Sistem Layanan Mahasiswa SmartStudent

Program ini adalah implementasi sistem layanan mahasiswa yang menggunakan 7 struktur data fundamental dalam C++. Program ini telah didesain untuk berjalan di **Windows** dan **Linux**.

## Struktur Data yang Diimplementasikan

1. **Linked List** - Untuk daftar mahasiswa
2. **Queue** - Untuk antrian layanan
3. **Stack** - Untuk riwayat transaksi
4. **Hash Table** - Untuk pencarian cepat mahasiswa
5. **Binary Search Tree (BST)** - Untuk data nilai
6. **Graph** - Untuk hubungan antar program studi
7. **Sorting & Searching** - Untuk pengurutan dan pencarian mahasiswa

## Struktur File

- `main.cpp` - File utama program (Cross-platform)
- `Student.h` - Struktur dasar mahasiswa
- `StudentList.h/.cpp` - Implementasi Linked List
- `ServiceQueue.h/.cpp` - Implementasi Queue
- `TransactionStack.h/.cpp` - Implementasi Stack
- `StudentHashTable.h/.cpp` - Implementasi Hash Table
- `BST.h/.cpp` - Implementasi Binary Search Tree
- `ProdiGraph.h/.cpp` - Implementasi Graph
- `StudentSorter.h/.cpp` - Implementasi Sorting & Searching

## Requirements

### Windows

- MinGW-w64 (untuk g++) atau Visual Studio 2017+
- Windows 7 atau lebih baru

### Linux

- g++ compiler (gcc 5.4+ recommended)
- Terminal yang mendukung ANSI escape sequences

## Cara Kompilasi dan Menjalankan

### Windows

#### Opsi 1: Menggunakan Batch Files (Recommended)

```cmd
# Kompilasi menggunakan g++ (MinGW)
build.bat

# Kompilasi menggunakan Visual Studio Compiler
build_msvc.bat

# Jalankan program
run.bat

# Bersihkan file build
clean.bat
```

#### Opsi 2: Menggunakan Makefile

```cmd
# Kompilasi program
make all

# Jalankan program
make run

# Bersihkan file build
make clean
```

### Linux

#### Opsi 1: Menggunakan Shell Scripts (Recommended)

```bash
# Berikan permission untuk execute
chmod +x build.sh run.sh clean.sh

# Kompilasi program
./build.sh

# Jalankan program
./run.sh

# Bersihkan file build
./clean.sh
```

#### Opsi 2: Menggunakan Makefile

```bash
# Kompilasi program
make all

# Jalankan program
make run

# Bersihkan file build
make clean
```

#### Opsi 3: Kompilasi Manual

```bash
# Kompilasi dengan g++
g++ -std=c++11 -Wall -Wextra -o SmartStudent main.cpp StudentList.cpp ServiceQueue.cpp TransactionStack.cpp StudentHashTable.cpp BST.cpp ProdiGraph.cpp StudentSorter.cpp

# Jalankan program
./SmartStudent
```

## Platform Differences

### Windows

- Menggunakan `_getch()` dari `<conio.h>` untuk input keyboard
- Menggunakan `system("cls")` untuk clear screen
- Arrow keys: Up=72, Down=80, Enter=13

### Linux

- Menggunakan `termios` untuk raw keyboard input
- Menggunakan `system("clear")` untuk clear screen
- Arrow keys: Up=65, Down=66, Enter=10

## Troubleshooting

### Windows

- Pastikan MinGW atau Visual Studio sudah terinstall
- Tambahkan g++ ke PATH jika menggunakan MinGW
- Jalankan Command Prompt sebagai Administrator jika ada error permission

### Linux

- Install g++ jika belum ada: `sudo apt-get install g++` (Ubuntu/Debian)
- Pastikan terminal mendukung arrow keys
- Berikan permission execute untuk script: `chmod +x *.sh`

# Jalankan program

make run

# Bersihkan file object

make clean-unix

````

### Kompilasi Manual

#### Windows dengan g++ (MinGW)

```cmd
g++ -std=c++11 -o SmartStudent.exe main.cpp StudentList.cpp ServiceQueue.cpp TransactionStack.cpp StudentHashTable.cpp BST.cpp ProdiGraph.cpp StudentSorter.cpp
````

#### Windows dengan Visual Studio Compiler

```cmd
cl.exe /EHsc /std:c++11 main.cpp StudentList.cpp ServiceQueue.cpp TransactionStack.cpp StudentHashTable.cpp BST.cpp ProdiGraph.cpp StudentSorter.cpp /Fe:SmartStudent.exe
```

#### Linux/Mac

```bash
g++ -std=c++11 -o SmartStudent main.cpp StudentList.cpp ServiceQueue.cpp TransactionStack.cpp StudentHashTable.cpp BST.cpp ProdiGraph.cpp StudentSorter.cpp
```

## Quick Start (Windows)

1. **Download dan Install Compiler:**

   - **Option 1**: Install MinGW-w64 dari [winlibs.com](https://winlibs.com/) atau [msys2.org](https://www.msys2.org/)
   - **Option 2**: Install Visual Studio Community dengan C++ workload

2. **Kompilasi Program:**

   ```cmd
   # Jika menggunakan MinGW/g++
   build.bat

   # Jika menggunakan Visual Studio
   build_msvc.bat
   ```

3. **Jalankan Program:**
   ```cmd
   run.bat
   ```

## Quick Start (Linux/Mac)

1. **Install Compiler:**

   ```bash
   # Ubuntu/Debian
   sudo apt install g++ make

   # CentOS/RHEL
   sudo yum install gcc-c++ make

   # macOS (dengan Homebrew)
   brew install gcc make
   ```

2. **Kompilasi dan Jalankan:**
   ```bash
   make all
   make run
   ```

## Fitur Program

### Menu Utama

1. **Linked List Operations**

   - Tambah mahasiswa
   - Tampilkan daftar mahasiswa
   - Hapus mahasiswa

2. **Queue Operations**

   - Tambah antrian layanan
   - Proses antrian
   - Tampilkan antrian

3. **Stack Operations**

   - Catat transaksi
   - Undo transaksi
   - Tampilkan riwayat transaksi

4. **Hash Table Operations**

   - Tambah data ke hash table
   - Cari mahasiswa
   - Tampilkan hash table

5. **BST Operations**

   - Tambah nilai ke BST
   - Tampilkan data nilai (in-order)

6. **Graph Operations**

   - Tambah hubungan antar prodi
   - Tampilkan hubungan prodi

7. **Sorting & Searching Operations**
   - Tambah mahasiswa untuk sorting
   - Urutkan berdasarkan nama
   - Urutkan berdasarkan NIM
   - Binary search berdasarkan NIM
   - Linear search berdasarkan nama
   - Tampilkan data sorter

## Keunggulan Versi Modular

1. **Maintainability** - Setiap struktur data dalam file terpisah
2. **Reusability** - Class dapat digunakan di project lain
3. **Readability** - Kode lebih mudah dibaca dan dipahami
4. **Scalability** - Mudah menambah fitur baru
5. **Debugging** - Lebih mudah mencari dan memperbaiki bug
6. **Team Development** - Tim dapat bekerja pada file berbeda

## Contoh Penggunaan

1. Jalankan program
2. Pilih menu sesuai operasi yang diinginkan
3. Ikuti instruksi untuk input data
4. Program akan menampilkan hasil operasi

## Requirements

- C++ Compiler yang mendukung C++11 atau lebih baru
- Standard Library C++
