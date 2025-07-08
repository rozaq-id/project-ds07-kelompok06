#include <iostream>
#include <string>
#include <vector>
#include <csignal>
#include <limits>
#include <algorithm>

// Platform-specific includes
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// Include semua header file
#include "StudentList.h"
#include "ServiceQueue.h"
#include "TransactionStack.h"
#include "StudentHashTable.h"
#include "BST.h"
#include "ProdiGraph.h"
#include "StudentSorter.h"

using namespace std;

// Cross-platform function untuk clear screen
void clearScreen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Cross-platform function untuk getch
int getch()
{
#ifdef _WIN32
  return _getch();
#else
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
#endif
}

// Menu interaktif dengan arrow key
int interactiveMenu(const std::vector<std::string> &options, const std::string &title)
{
  int selected = 0;
  int n = static_cast<int>(options.size());
  // Hitung lebar kotak minimal 30, atau lebih jika judul lebih panjang
  int titleLen = static_cast<int>(title.length());
  int boxWidth = (titleLen + 6 > 30) ? (titleLen + 6) : 30;
  auto isSeparator = [](const std::string &s)
  {
    return s == "\n" || s.find("--->") != std::string::npos;
  };
  // Cari pertama yang bukan separator
  while (selected < n && isSeparator(options[selected]))
    ++selected;
  while (true)
  {
    clearScreen();
    // Baris atas kotak
    std::cout << std::string(boxWidth, '=') << "\n";
    // Judul di tengah kotak
    int padding = (boxWidth - titleLen - 2) / 2;
    std::cout << "=" << std::string(padding, ' ') << title << std::string(boxWidth - padding - titleLen - 2, ' ') << "=" << std::endl;
    // Baris bawah judul
    std::cout << std::string(boxWidth, '=') << "\n";
    for (int i = 0; i < n; ++i)
    {
      if (i == selected)
        std::cout << " > ";
      else
        std::cout << "   ";
      std::cout << options[i] << std::endl;
    }
    std::cout << "----------------------------------------\n";
    std::cout << "Info: Gunakan panah atas/bawah untuk navigasi, Enter untuk memilih\n";
    int ch = getch();
    if (ch == 224 || ch == 27)
    { // Arrow key (224 for Windows, 27 for Linux ESC sequence)
#ifdef _WIN32
      ch = getch();
      if (ch == 72) // Up arrow
#else
      if (ch == 27)
      {
        ch = getch(); // '['
        ch = getch(); // Direction
      }
      if (ch == 65) // Up arrow in Linux
#endif
      {
        int next = selected;
        do
        {
          next = (next - 1 + n) % n;
        } while (isSeparator(options[next]));
        selected = next;
      }
#ifdef _WIN32
      if (ch == 80) // Down arrow
#else
      if (ch == 66) // Down arrow in Linux
#endif
      {
        int next = selected;
        do
        {
          next = (next + 1) % n;
        } while (isSeparator(options[next]));
        selected = next;
      }
    }
    else if (ch == 13 || ch == 10)
    { // Enter (13 for Windows, 10 for Linux)
      if (!isSeparator(options[selected]))
        return selected;
    }
  }
}

// Form input dengan tampilan rapi dan opsi cancel
void inputForm(const std::vector<std::string> &fields, std::vector<std::string> &results, bool allowCancel = true)
{
  results.clear();
  std::cout << "Info: Ketik 'cancel' untuk membatalkan input\n";
  std::cout << "----------------------------------------\n";
  for (const auto &field : fields)
  {
    std::string value;
    std::cout << field << ": ";
    std::getline(std::cin, value);

    if (allowCancel && value == "cancel")
    {
      results.clear();
      std::cout << "Input dibatalkan.\n";
      return;
    }
    results.push_back(value);
  }
}

// Fungsi utama
int main()
{
  StudentList list;
  ServiceQueue queue;
  TransactionStack stack;
  StudentHashTable hashTable;
  BST bst;
  ProdiGraph graph(3);
  StudentSorter sorter;

  // Inisialisasi data prodi untuk graph
  graph.addProdi("Informatika", 0);
  graph.addProdi("Sistem Informasi", 1);
  graph.addProdi("Manajemen", 2);

  std::vector<std::string> menu = {
      "1. Linked List --->",
      "* Tambah Mahasiswa",
      "* Tampilkan Daftar Mahasiswa",
      "* Hapus Mahasiswa\n",
      "2. Queue --->",
      "* Tambah Antrian Layanan",
      "* Proses Antrian Layanan",
      "* Tampilkan Antrian\n",
      "3. Stack --->",
      "* Catat Transaksi",
      "* Undo Transaksi",
      "* Tampilkan Riwayat Transaksi\n",
      "4. Hash Table --->",
      "* Tambah Data ke Hash Table",
      "* Cari Mahasiswa di Hash Table",
      "* Tampilkan Hash Table\n",
      "5. Tree (BST) --->",
      "* Tambah Nilai ke BST",
      "* Tampilkan Data Nilai\n",
      "6. Graph --->",
      "* Tambah Hubungan Prodi",
      "* Tampilkan Hubungan Prodi\n",
      "7. Sorting & Searching --->",
      "* Urutkan Mahasiswa berdasarkan Nama",
      "* Urutkan Mahasiswa berdasarkan NIM",
      "* Cari Mahasiswa berdasarkan NIM (Binary Search)",
      "* Cari Mahasiswa berdasarkan Nama (Linear Search)",
      "* Tampilkan Data Sorting\n",
      "* Keluar"};

  int choice = 0;
  do
  {
    choice = interactiveMenu(menu, "Sistem Layanan Mahasiswa SmartStudent");
    clearScreen();
    std::string nim, name, prodi, service, transaction;
    int score, prodi1, prodi2;
    std::vector<std::string> results;
    switch (choice)
    {
    case 1: // Tambah Mahasiswa
      clearScreen();
      std::cout << "==== Tambah Mahasiswa (Linked List) ====" << std::endl;
      inputForm({"NIM", "Nama", "Prodi"}, results);
      if (results.empty())
        break;
      list.addStudent(results[0], results[1], results[2]);
      std::cout << "Mahasiswa berhasil ditambah!\n";
      break;
    case 2: // Tampilkan Daftar Mahasiswa
      clearScreen();
      std::cout << "==== Daftar Mahasiswa (Linked List) ====" << std::endl;
      list.display();
      break;
    case 3: // Hapus Mahasiswa
      clearScreen();
      std::cout << "==== Hapus Mahasiswa (Linked List) ====" << std::endl;
      inputForm({"NIM yang akan dihapus"}, results);
      if (results.empty())
        break;
      list.deleteStudent(results[0]);
      break;
    case 5: // Tambah Antrian Layanan
      clearScreen();
      std::cout << "==== Tambah Antrian Layanan (Queue) ====" << std::endl;
      inputForm({"NIM", "Layanan"}, results);
      if (results.empty())
        break;
      queue.enqueue(results[0], results[1]);
      break;
    case 6: // Proses Antrian Layanan
      clearScreen();
      std::cout << "==== Proses Antrian Layanan (Queue) ====" << std::endl;
      queue.dequeue();
      break;
    case 7: // Tampilkan Antrian
      clearScreen();
      std::cout << "==== Daftar Antrian (Queue) ====" << std::endl;
      queue.display();
      break;
    case 9: // Catat Transaksi
      clearScreen();
      std::cout << "==== Catat Transaksi (Stack) ====" << std::endl;
      inputForm({"Transaksi"}, results);
      if (results.empty())
        break;
      stack.push(results[0]);
      break;
    case 10: // Undo Transaksi
      clearScreen();
      std::cout << "==== Undo Transaksi (Stack) ====" << std::endl;
      stack.pop();
      break;
    case 11: // Tampilkan Riwayat Transaksi
      clearScreen();
      std::cout << "==== Riwayat Transaksi (Stack) ====" << std::endl;
      stack.display();
      break;
    case 13: // Tambah Data ke Hash Table
      clearScreen();
      std::cout << "==== Tambah Data ke Hash Table ====" << std::endl;
      inputForm({"NIM", "Nama", "Prodi"}, results);
      if (results.empty())
        break;
      hashTable.insert(results[0], results[1], results[2]);
      break;
    case 14: // Cari Mahasiswa di Hash Table
      clearScreen();
      std::cout << "==== Cari Mahasiswa di Hash Table ====" << std::endl;
      inputForm({"NIM"}, results);
      if (results.empty())
        break;
      hashTable.search(results[0]);
      break;
    case 15: // Tampilkan Hash Table
      clearScreen();
      std::cout << "==== Tampilkan Hash Table ====" << std::endl;
      hashTable.display();
      break;
    case 17: // Tambah Nilai ke BST
      clearScreen();
      std::cout << "==== Tambah Nilai ke BST ====" << std::endl;
      inputForm({"NIM", "Nilai"}, results);
      if (results.empty())
        break;
      score = std::stoi(results[1]);
      bst.insert(results[0], score);
      break;
    case 18: // Tampilkan Data Nilai
      clearScreen();
      std::cout << "==== Data Nilai (BST) ====" << std::endl;
      bst.display();
      break;
    case 20: // Tambah Hubungan Prodi
      clearScreen();
      std::cout << "==== Tambah Hubungan Prodi (Graph) ====" << std::endl;
      inputForm({"Indeks Prodi 1 (0-2)", "Indeks Prodi 2 (0-2)"}, results);
      if (results.empty())
        break;
      prodi1 = std::stoi(results[0]);
      prodi2 = std::stoi(results[1]);
      graph.addEdge(prodi1, prodi2);
      break;
    case 21: // Tampilkan Hubungan Prodi
      clearScreen();
      std::cout << "==== Hubungan Prodi (Graph) ====" << std::endl;
      graph.display();
      break;
    case 23: // Urutkan Mahasiswa berdasarkan Nama
      clearScreen();
      std::cout << "==== Urutkan Mahasiswa berdasarkan Nama ====" << std::endl;
      sorter.clearData();
      list.exportToSorter(sorter);
      sorter.sortByName();
      break;
    case 24: // Urutkan Mahasiswa berdasarkan NIM
      clearScreen();
      std::cout << "==== Urutkan Mahasiswa berdasarkan NIM ====" << std::endl;
      sorter.clearData();
      list.exportToSorter(sorter);
      sorter.sortByNIM();
      break;
    case 25: // Cari Mahasiswa berdasarkan NIM (Binary Search)
      clearScreen();
      std::cout << "==== Cari Mahasiswa berdasarkan NIM (Binary Search) ====" << std::endl;
      sorter.clearData();
      list.exportToSorter(sorter);
      inputForm({"NIM"}, results);
      if (results.empty())
        break;
      sorter.searchByNIM(results[0]);
      break;
    case 26: // Cari Mahasiswa berdasarkan Nama (Linear Search)
      clearScreen();
      std::cout << "==== Cari Mahasiswa berdasarkan Nama (Linear Search) ====" << std::endl;
      sorter.clearData();
      list.exportToSorter(sorter);
      inputForm({"Nama yang dicari"}, results);
      if (results.empty())
        break;
      sorter.linearSearchByName(results[0]);
      break;
    case 27: // Tampilkan Data Sorting
      clearScreen();
      std::cout << "==== Data Sorting ====" << std::endl;
      sorter.clearData();
      list.exportToSorter(sorter);
      sorter.display();
      break;
    case 28: // Keluar
      clearScreen();
      std::cout << "Keluar dari program.\n";
      break;
    default:
      clearScreen();
      std::cout << "Pilihan tidak valid.\n";
    }
    if (choice != 28)
    {
      std::cout << "\nTekan apapun untuk kembali ke menu...";
      getch();
    }
  } while (choice != 28);

  return 0;
}
