/*
===============================================================================
                    SMARTSTUDENT - SISTEM LAYANAN MAHASISWA DIGITAL
                              KAMPUS CAKRAWALA
===============================================================================

ANALISIS STRUKTUR DATA YANG DIGUNAKAN:

a. STRUKTUR DATA UNTUK SETIAP FITUR:

1. DAFTAR BUKU PERPUSTAKAAN - LINKED LIST
   - Alasan: Memungkinkan penambahan/penghapusan buku yang dinamis tanpa
     perlu alokasi memori tetap. Cocok untuk data yang sering berubah.
   - Kelebihan: Efisien untuk insert/delete, fleksibel ukuran
   - Kekurangan: Pencarian sequential O(n), tidak ada random access

2. ANTREAN KONSULTASI AKADEMIK - QUEUE (FIFO)
   - Alasan: Sistem antrian harus mengikuti prinsip first-in-first-out
     untuk menjaga keadilan pelayanan konsultasi.
   - Kelebihan: Adil, operasi enqueue/dequeue O(1)
   - Kekurangan: Tidak bisa mengakses elemen di tengah

3. LOGIN MAHASISWA - HASH TABLE
   - Alasan: Pencarian user berdasarkan NIM harus sangat cepat O(1) average case.
     Hash table optimal untuk key-value lookup dengan performa tinggi.
   - Kelebihan: Pencarian sangat cepat, efisien memori
   - Kekurangan: Potensi collision, tidak terurut

4. RIWAYAT AKTIVITAS MAHASISWA - STACK (LIFO)
   - Alasan: Aktivitas terbaru lebih penting dan sering diakses.
     Stack memungkinkan akses cepat ke aktivitas terakhir.
   - Kelebihan: Push/pop O(1), cocok untuk tracking aktivitas terbaru
   - Kekurangan: Tidak bisa akses random, LIFO bisa tidak sesuai semua kasus

5. RIWAYAT PEMINJAMAN BUKU - LINKED LIST
   - Alasan: Record peminjaman perlu disimpan permanen dan bisa bertambah
     terus. Linked list memberikan fleksibilitas dan efisiensi memori.
   - Kelebihan: Dinamis, bisa menyimpan data relasional
   - Kekurangan: Pencarian sequential, konsumsi memori pointer

6. NAVIGASI LOKASI KAMPUS - GRAPH (WEIGHTED & UNDIRECTED)
   - Alasan: Representasi lokasi dan jalur antar bangunan memerlukan struktur
     yang dapat merepresentasikan hubungan many-to-many dengan bobot jarak.
   - Kelebihan: Dapat merepresentasikan jalur kompleks, algoritma shortest path
   - Kekurangan: Kompleks implementasi, memori besar untuk dense graph

7. SORTING & SEARCHING BUKU - ARRAY/VECTOR dengan BINARY SEARCH
   - Alasan: Untuk pencarian cepat, data perlu diurutkan terlebih dahulu.
     Binary search memberikan kompleksitas O(log n).
   - Kelebihan: Pencarian sangat cepat setelah diurutkan
   - Kekurangan: Perlu sorting dulu, update data lambat

b. GRAPH DALAM SISTEM NAVIGASI KAMPUS:

KELEBIHAN GRAPH:
- Dapat merepresentasikan hubungan kompleks antar lokasi
- Mendukung multiple path antara dua titik
- Dapat mengimplementasikan algoritma shortest path (Dijkstra, Floyd-Warshall)
- Fleksibel untuk menambah/menghapus lokasi dan jalur
- Dapat menyimpan informasi tambahan (jarak, waktu tempuh, dll)

KEKURANGAN GRAPH:
- Implementasi lebih kompleks dibanding struktur data linear
- Konsumsi memori besar untuk graph yang dense
- Algoritma pencarian jalur memiliki kompleksitas tinggi
- Sulit untuk debugging dan maintenance
- Perlu algoritma khusus untuk operasi umum

PERBEDAAN GRAPH BERARAH VS TAK BERARAH:

GRAPH TAK BERARAH (Undirected):
- Jalur dua arah: A -> B sama dengan B -> A
- Cocok untuk: jalan raya, koridor, jalur pejalan kaki
- Representasi: jika ada edge (A,B) maka otomatis ada (B,A)
- Contoh: Perpustakaan ↔ Gedung Informatika

GRAPH BERARAH (Directed):
- Jalur satu arah: A -> B tidak sama dengan B -> A
- Cocok untuk: jalur evakuasi, escalator, one-way road
- Representasi: edge (A,B) tidak berarti ada (B,A)
- Contoh: Tangga darurat (hanya turun), lift (khusus untuk disable)

c. SIMULASI ALUR MAHASISWA:

ALUR: Login → Antre Konsultasi → Pinjam Buku → Lihat Riwayat Aktivitas

1. LOGIN:
   - Struktur Data: HASH TABLE (LoginSystem)
   - Operasi: Cek NIM & password, buat session
   - Kompleksitas: O(1) average case

2. ANTRE KONSULTASI:
   - Struktur Data: QUEUE (ServiceQueue)
   - Operasi: enqueue(nim, jenis_konsultasi)
   - Kompleksitas: O(1)
   - Log aktivitas ke STACK (ActivityHistory)

3. PINJAM BUKU:
   - Struktur Data: LINKED LIST (BookLibrary) + LINKED LIST (BorrowingHistory)
   - Operasi: Cari buku, update status, catat peminjaman
   - Kompleksitas: O(n) untuk pencarian buku
   - Log aktivitas ke STACK (ActivityHistory)

4. LIHAT RIWAYAT AKTIVITAS:
   - Struktur Data: STACK (ActivityHistory)
   - Operasi: Tampilkan aktivitas user dari top stack
   - Kompleksitas: O(n) untuk filter berdasarkan NIM

INTEGRASI ANTAR STRUKTUR DATA:
- Hash Table menyimpan session untuk akses cepat user info
- Stack mencatat semua aktivitas untuk audit trail
- Queue mengelola antrian secara fair dan efisien
- Linked List memberikan fleksibilitas untuk data dinamis
- Graph memungkinkan navigasi optimal di kampus

===============================================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <csignal>
#include <limits>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <tuple>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>

// Platform-specific includes
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

// ===== UTILITY CLASSES =====

// Struktur untuk Buku
struct Book
{
  string id, title, author, category;
  bool isAvailable;
  Book *next;
  Book(string _id, string _title, string _author, string _category)
      : id(_id), title(_title), author(_author), category(_category), isAvailable(true), next(nullptr) {}
};

// Struktur untuk Login Session
struct LoginSession
{
  string nim, name, loginTime;
  bool isActive;
  LoginSession(string _nim, string _name, string _loginTime)
      : nim(_nim), name(_name), loginTime(_loginTime), isActive(true) {}
};

// Struktur untuk Activity Record
struct Activity
{
  string nim, activity, timestamp;
  Activity *next;
  Activity(string _nim, string _activity, string _timestamp)
      : nim(_nim), activity(_activity), timestamp(_timestamp), next(nullptr) {}
};

// Struktur untuk Borrowing Record
struct BorrowRecord
{
  string nim, bookId, borrowDate, returnDate;
  bool isReturned;
  BorrowRecord *next;
  BorrowRecord(string _nim, string _bookId, string _borrowDate)
      : nim(_nim), bookId(_bookId), borrowDate(_borrowDate), returnDate(""), isReturned(false), next(nullptr) {}
};

// ===== STUDENT STRUCTURE =====
struct Student
{
  string nim, name, prodi;
  Student *next;
  Student(string _nim, string _name, string _prodi) : nim(_nim), name(_name), prodi(_prodi), next(nullptr) {}
};

// ===== STUDENTLIST CLASS =====
class StudentList
{
private:
  Student *head;

public:
  StudentList() : head(nullptr) {}

  ~StudentList()
  {
    while (head)
    {
      Student *temp = head;
      head = head->next;
      delete temp;
    }
  }

  void addStudent(string nim, string name, string prodi)
  {
    if (findByNIM(nim))
    {
      cout << "NIM " << nim << " sudah terdaftar!\n";
      return;
    }

    Student *newStudent = new Student(nim, name, prodi);
    if (!head)
    {
      head = newStudent;
    }
    else
    {
      Student *temp = head;
      while (temp->next)
        temp = temp->next;
      temp->next = newStudent;
    }
    cout << "Mahasiswa " << name << " ditambahkan.\n";
  }

  Student *findByNIM(string nim)
  {
    Student *temp = head;
    while (temp)
    {
      if (temp->nim == nim)
        return temp;
      temp = temp->next;
    }
    return nullptr;
  }

  void deleteStudent(string nim)
  {
    if (!head)
    {
      cout << "Daftar mahasiswa kosong.\n";
      return;
    }

    if (head->nim == nim)
    {
      Student *temp = head;
      head = head->next;
      cout << "Mahasiswa " << temp->name << " dihapus.\n";
      delete temp;
      return;
    }

    Student *current = head;
    while (current->next && current->next->nim != nim)
    {
      current = current->next;
    }

    if (current->next)
    {
      Student *temp = current->next;
      current->next = temp->next;
      cout << "Mahasiswa " << temp->name << " dihapus.\n";
      delete temp;
    }
    else
    {
      cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
  }

  void display()
  {
    Student *temp = head;
    if (!temp)
    {
      cout << "Daftar mahasiswa kosong.\n";
      return;
    }
    cout << "\n=== Daftar Mahasiswa ===\n";
    int count = 1;
    while (temp)
    {
      cout << count << ". NIM: " << temp->nim
           << ", Nama: " << temp->name
           << ", Prodi: " << temp->prodi << "\n";
      temp = temp->next;
      count++;
    }
  }

  void exportToSorter(class StudentSorter &sorter); // Forward declaration
};

// ===== SERVICEQUEUE CLASS =====
class ServiceQueue
{
private:
  struct Node
  {
    string nim, service;
    Node *next;
    Node(string _nim, string _service) : nim(_nim), service(_service), next(nullptr) {}
  };
  Node *front;
  Node *rear;
  int size;

public:
  ServiceQueue() : front(nullptr), rear(nullptr), size(0) {}

  ~ServiceQueue()
  {
    while (front)
    {
      Node *temp = front;
      front = front->next;
      delete temp;
    }
  }

  void enqueue(string nim, string service)
  {
    Node *newNode = new Node(nim, service);
    if (!rear)
    {
      front = rear = newNode;
    }
    else
    {
      rear->next = newNode;
      rear = newNode;
    }
    size++;
    cout << "Antrian untuk " << nim << " (" << service << ") ditambahkan. Posisi: " << size << "\n";
  }

  void dequeue()
  {
    if (!front)
    {
      cout << "Antrian kosong.\n";
      return;
    }
    Node *temp = front;
    cout << "Melayani " << temp->nim << " untuk " << temp->service << "\n";
    front = front->next;
    if (!front)
      rear = nullptr;
    delete temp;
    size--;
  }

  void display()
  {
    if (!front)
    {
      cout << "Antrian kosong.\n";
      return;
    }

    cout << "\n=== Antrian Layanan ===\n";
    Node *temp = front;
    int pos = 1;
    while (temp)
    {
      cout << pos << ". NIM: " << temp->nim << " - Layanan: " << temp->service << "\n";
      temp = temp->next;
      pos++;
    }
    cout << "Total antrian: " << size << "\n";
  }

  int getSize() { return size; }
};

// ===== TRANSACTIONSTACK CLASS =====
class TransactionStack
{
private:
  struct Node
  {
    string transaction;
    string timestamp;
    Node *next;
    Node(string _transaction, string _timestamp) : transaction(_transaction), timestamp(_timestamp), next(nullptr) {}
  };
  Node *top;
  int size;

public:
  TransactionStack() : top(nullptr), size(0) {}

  ~TransactionStack()
  {
    while (top)
    {
      Node *temp = top;
      top = top->next;
      delete temp;
    }
  }

  string getCurrentTime()
  {
    return "2025-07-08 10:00:00"; // Simplified timestamp
  }

  void push(string transaction)
  {
    Node *newNode = new Node(transaction, getCurrentTime());
    newNode->next = top;
    top = newNode;
    size++;
    cout << "Transaksi: " << transaction << " dicatat pada " << newNode->timestamp << "\n";
  }

  void pop()
  {
    if (!top)
    {
      cout << "Riwayat transaksi kosong.\n";
      return;
    }
    Node *temp = top;
    cout << "Undo transaksi: " << temp->transaction << " (pada " << temp->timestamp << ")\n";
    top = top->next;
    delete temp;
    size--;
  }

  void display()
  {
    if (!top)
    {
      cout << "Riwayat transaksi kosong.\n";
      return;
    }

    cout << "\n=== Riwayat Transaksi ===\n";
    Node *temp = top;
    int count = 1;
    while (temp)
    {
      cout << count << ". " << temp->transaction << " (pada " << temp->timestamp << ")\n";
      temp = temp->next;
      count++;
    }
    cout << "Total transaksi: " << size << "\n";
  }

  int getSize() { return size; }
};

// ===== STUDENTHASHTABLE CLASS =====
class StudentHashTable
{
private:
  unordered_map<string, pair<string, string>> table; // NIM -> {Nama, Prodi}

public:
  void insert(string nim, string name, string prodi)
  {
    table[nim] = make_pair(name, prodi);
    cout << "Data " << name << " disimpan di hash table.\n";
  }

  void search(string nim)
  {
    if (table.find(nim) != table.end())
    {
      cout << "Mahasiswa ditemukan:\n";
      cout << "  NIM: " << nim << "\n";
      cout << "  Nama: " << table[nim].first << "\n";
      cout << "  Prodi: " << table[nim].second << "\n";
    }
    else
    {
      cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
  }

  void remove(string nim)
  {
    if (table.find(nim) != table.end())
    {
      cout << "Data mahasiswa " << table[nim].first << " dihapus dari hash table.\n";
      table.erase(nim);
    }
    else
    {
      cout << "Data dengan NIM " << nim << " tidak ditemukan.\n";
    }
  }

  void display()
  {
    if (table.empty())
    {
      cout << "Hash table kosong.\n";
      return;
    }

    cout << "\n=== Data Hash Table ===\n";
    int count = 1;
    for (auto &entry : table)
    {
      cout << count << ". NIM: " << entry.first
           << ", Nama: " << entry.second.first
           << ", Prodi: " << entry.second.second << "\n";
      count++;
    }
  }

  int getSize() { return table.size(); }
};

// ===== BST CLASS =====
class BST
{
private:
  struct Node
  {
    string nim;
    int score;
    Node *left, *right;
    Node(string _nim, int _score) : nim(_nim), score(_score), left(nullptr), right(nullptr) {}
  };
  Node *root;

  Node *insert(Node *node, string nim, int score)
  {
    if (!node)
      return new Node(nim, score);
    if (score < node->score)
      node->left = insert(node->left, nim, score);
    else
      node->right = insert(node->right, nim, score);
    return node;
  }

  void inOrder(Node *node)
  {
    if (node)
    {
      inOrder(node->left);
      cout << "NIM: " << node->nim << ", Nilai: " << node->score << "\n";
      inOrder(node->right);
    }
  }

public:
  BST() : root(nullptr) {}

  void insert(string nim, int score)
  {
    root = insert(root, nim, score);
    cout << "Nilai " << score << " untuk " << nim << " ditambahkan ke BST.\n";
  }

  void display()
  {
    if (!root)
    {
      cout << "BST kosong.\n";
      return;
    }
    cout << "\n=== Data Nilai (In-Order) ===\n";
    inOrder(root);
  }
};

// ===== PRODIGRAPH CLASS =====
class ProdiGraph
{
private:
  vector<vector<int>> adjMatrix;
  vector<string> prodiList;

public:
  ProdiGraph(int size)
  {
    adjMatrix.resize(size, vector<int>(size, 0));
    prodiList.resize(size);
  }

  void addProdi(string prodi, int index)
  {
    prodiList[index] = prodi;
  }

  void addEdge(int i, int j)
  {
    adjMatrix[i][j] = 1;
    adjMatrix[j][i] = 1;
    cout << "Hubungan antara " << prodiList[i] << " dan " << prodiList[j] << " ditambahkan.\n";
  }

  void display()
  {
    cout << "\n=== Hubungan antar prodi ===\n";
    for (size_t i = 0; i < prodiList.size(); i++)
    {
      cout << prodiList[i] << ": ";
      for (size_t j = 0; j < prodiList.size(); j++)
      {
        if (adjMatrix[i][j])
          cout << prodiList[j] << " ";
      }
      cout << "\n";
    }
  }
};

// ===== STUDENTSORTER CLASS =====
class StudentSorter
{
private:
  vector<tuple<string, string, string>> students; // Nama, NIM, Prodi

  void sortByNIMSilent()
  {
    sort(students.begin(), students.end(), [](const tuple<string, string, string> &a, const tuple<string, string, string> &b)
         { return get<1>(a) < get<1>(b); });
  }

public:
  void addStudent(string name, string nim, string prodi)
  {
    students.push_back(make_tuple(name, nim, prodi));
    cout << "Mahasiswa " << name << " ditambahkan ke sorter.\n";
  }

  void clearData()
  {
    students.clear();
  }

  void sortByName()
  {
    sort(students.begin(), students.end());
    cout << "\n=== Daftar Mahasiswa (Urut Nama) ===\n";
    for (size_t i = 0; i < students.size(); i++)
    {
      cout << (i + 1) << ". Nama: " << get<0>(students[i])
           << ", NIM: " << get<1>(students[i])
           << ", Prodi: " << get<2>(students[i]) << "\n";
    }
  }

  void sortByNIM()
  {
    sort(students.begin(), students.end(), [](const tuple<string, string, string> &a, const tuple<string, string, string> &b)
         { return get<1>(a) < get<1>(b); });
    cout << "\n=== Daftar Mahasiswa (Urut NIM) ===\n";
    for (size_t i = 0; i < students.size(); i++)
    {
      cout << (i + 1) << ". NIM: " << get<1>(students[i])
           << ", Nama: " << get<0>(students[i])
           << ", Prodi: " << get<2>(students[i]) << "\n";
    }
  }

  void searchByNIM(string nim)
  {
    sortByNIMSilent();
    int left = 0, right = students.size() - 1;
    bool found = false;

    while (left <= right)
    {
      int mid = left + (right - left) / 2;
      string midNIM = get<1>(students[mid]);

      if (midNIM == nim)
      {
        cout << "Ditemukan: " << get<0>(students[mid])
             << " (NIM: " << nim << ", Prodi: " << get<2>(students[mid]) << ")\n";
        found = true;
        break;
      }

      if (midNIM < nim)
      {
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }

    if (!found)
    {
      cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
  }

  void linearSearchByName(string name)
  {
    bool found = false;
    cout << "Hasil pencarian untuk nama '" << name << "':\n";

    for (const auto &student : students)
    {
      if (get<0>(student).find(name) != string::npos)
      {
        cout << "Ditemukan: " << get<0>(student)
             << " (NIM: " << get<1>(student)
             << ", Prodi: " << get<2>(student) << ")\n";
        found = true;
      }
    }

    if (!found)
    {
      cout << "Tidak ada mahasiswa dengan nama yang mengandung '" << name << "'\n";
    }
  }

  void display()
  {
    if (students.empty())
    {
      cout << "Data sorter kosong.\n";
      return;
    }

    cout << "\n=== Data Mahasiswa Sorter ===\n";
    for (size_t i = 0; i < students.size(); i++)
    {
      cout << (i + 1) << ". Nama: " << get<0>(students[i])
           << ", NIM: " << get<1>(students[i])
           << ", Prodi: " << get<2>(students[i]) << "\n";
    }
  }
};

// ===== BOOK LIBRARY CLASS (Using Linked List) =====
class BookLibrary
{
private:
  Book *head;

public:
  BookLibrary() : head(nullptr) {}

  ~BookLibrary()
  {
    while (head)
    {
      Book *temp = head;
      head = head->next;
      delete temp;
    }
  }

  void addBook(string id, string title, string author, string category)
  {
    Book *newBook = new Book(id, title, author, category);
    if (!head)
    {
      head = newBook;
    }
    else
    {
      Book *temp = head;
      while (temp->next)
        temp = temp->next;
      temp->next = newBook;
    }
    cout << "Buku '" << title << "' berhasil ditambahkan ke perpustakaan.\n";
  }

  Book *findBookById(string id)
  {
    Book *temp = head;
    while (temp)
    {
      if (temp->id == id)
        return temp;
      temp = temp->next;
    }
    return nullptr;
  }

  void displayBooks()
  {
    if (!head)
    {
      cout << "Perpustakaan kosong.\n";
      return;
    }
    cout << "\n=== Daftar Buku Perpustakaan ===\n";
    Book *temp = head;
    int count = 1;
    while (temp)
    {
      cout << count << ". ID: " << temp->id
           << ", Judul: " << temp->title
           << ", Pengarang: " << temp->author
           << ", Kategori: " << temp->category
           << ", Status: " << (temp->isAvailable ? "Tersedia" : "Dipinjam") << "\n";
      temp = temp->next;
      count++;
    }
  }

  void searchBooks(string keyword)
  {
    bool found = false;
    Book *temp = head;
    cout << "\n=== Hasil Pencarian Buku ===\n";
    while (temp)
    {
      if (temp->title.find(keyword) != string::npos ||
          temp->author.find(keyword) != string::npos ||
          temp->category.find(keyword) != string::npos)
      {
        cout << "ID: " << temp->id
             << ", Judul: " << temp->title
             << ", Pengarang: " << temp->author
             << ", Status: " << (temp->isAvailable ? "Tersedia" : "Dipinjam") << "\n";
        found = true;
      }
      temp = temp->next;
    }
    if (!found)
    {
      cout << "Tidak ada buku yang ditemukan dengan kata kunci '" << keyword << "'\n";
    }
  }
};

// ===== LOGIN SYSTEM CLASS (Using Hash Table) =====
class LoginSystem
{
private:
  unordered_map<string, pair<string, string>> userDatabase; // NIM -> {password, name}
  LoginSession *currentSession;

public:
  LoginSystem() : currentSession(nullptr) {}

  ~LoginSystem()
  {
    if (currentSession)
      delete currentSession;
  }

  void registerUser(string nim, string password, string name)
  {
    userDatabase[nim] = make_pair(password, name);
    cout << "User " << name << " berhasil terdaftar.\n";
  }

  bool login(string nim, string password)
  {
    if (userDatabase.find(nim) != userDatabase.end())
    {
      if (userDatabase[nim].first == password)
      {
        if (currentSession)
          delete currentSession;

        time_t now = time(0);
        char *timeStr = ctime(&now);
        string loginTime(timeStr);
        loginTime.pop_back(); // Remove newline

        currentSession = new LoginSession(nim, userDatabase[nim].second, loginTime);
        cout << "Login berhasil! Selamat datang, " << userDatabase[nim].second << "\n";
        return true;
      }
      else
      {
        cout << "Password salah!\n";
        return false;
      }
    }
    else
    {
      cout << "NIM tidak terdaftar!\n";
      return false;
    }
  }

  void logout()
  {
    if (currentSession && currentSession->isActive)
    {
      cout << "Logout berhasil. Sampai jumpa, " << currentSession->name << "!\n";
      currentSession->isActive = false;
      delete currentSession;
      currentSession = nullptr;
    }
    else
    {
      cout << "Tidak ada sesi aktif.\n";
    }
  }

  bool isLoggedIn()
  {
    return currentSession && currentSession->isActive;
  }

  string getCurrentUser()
  {
    if (currentSession && currentSession->isActive)
    {
      return currentSession->nim;
    }
    return "";
  }

  string getCurrentUserName()
  {
    if (currentSession && currentSession->isActive)
    {
      return currentSession->name;
    }
    return "";
  }

  void displayCurrentSession()
  {
    if (currentSession && currentSession->isActive)
    {
      cout << "\n=== Sesi Login Aktif ===\n";
      cout << "NIM: " << currentSession->nim << "\n";
      cout << "Nama: " << currentSession->name << "\n";
      cout << "Waktu Login: " << currentSession->loginTime << "\n";
    }
    else
    {
      cout << "Tidak ada sesi aktif.\n";
    }
  }
};

// ===== ACTIVITY HISTORY CLASS (Using Stack) =====
class ActivityHistory
{
private:
  Activity *top;
  int size;

  string getCurrentTime()
  {
    time_t now = time(0);
    char *timeStr = ctime(&now);
    string timestamp(timeStr);
    timestamp.pop_back(); // Remove newline
    return timestamp;
  }

public:
  ActivityHistory() : top(nullptr), size(0) {}

  ~ActivityHistory()
  {
    while (top)
    {
      Activity *temp = top;
      top = top->next;
      delete temp;
    }
  }

  void addActivity(string nim, string activity)
  {
    Activity *newActivity = new Activity(nim, activity, getCurrentTime());
    newActivity->next = top;
    top = newActivity;
    size++;
    cout << "Aktivitas '" << activity << "' tercatat untuk " << nim << "\n";
  }

  void displayUserActivities(string nim)
  {
    if (!top)
    {
      cout << "Riwayat aktivitas kosong.\n";
      return;
    }

    cout << "\n=== Riwayat Aktivitas " << nim << " ===\n";
    Activity *temp = top;
    int count = 1;
    bool found = false;

    while (temp)
    {
      if (temp->nim == nim)
      {
        cout << count << ". " << temp->activity
             << " (pada " << temp->timestamp << ")\n";
        found = true;
        count++;
      }
      temp = temp->next;
    }

    if (!found)
    {
      cout << "Tidak ada aktivitas untuk NIM " << nim << "\n";
    }
  }

  void displayAllActivities()
  {
    if (!top)
    {
      cout << "Riwayat aktivitas kosong.\n";
      return;
    }

    cout << "\n=== Semua Riwayat Aktivitas ===\n";
    Activity *temp = top;
    int count = 1;
    while (temp)
    {
      cout << count << ". " << temp->nim << " - " << temp->activity
           << " (pada " << temp->timestamp << ")\n";
      temp = temp->next;
      count++;
    }
  }
};

// ===== BORROWING HISTORY CLASS (Using Linked List) =====
class BorrowingHistory
{
private:
  BorrowRecord *head;

  string getCurrentDate()
  {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
       << setfill('0') << setw(2) << (ltm->tm_mon + 1) << "/"
       << (ltm->tm_year + 1900);
    return ss.str();
  }

public:
  BorrowingHistory() : head(nullptr) {}

  ~BorrowingHistory()
  {
    while (head)
    {
      BorrowRecord *temp = head;
      head = head->next;
      delete temp;
    }
  }

  void borrowBook(string nim, string bookId)
  {
    BorrowRecord *newRecord = new BorrowRecord(nim, bookId, getCurrentDate());
    if (!head)
    {
      head = newRecord;
    }
    else
    {
      BorrowRecord *temp = head;
      while (temp->next)
        temp = temp->next;
      temp->next = newRecord;
    }
    cout << "Peminjaman buku " << bookId << " oleh " << nim << " tercatat.\n";
  }

  void returnBook(string nim, string bookId)
  {
    BorrowRecord *temp = head;
    while (temp)
    {
      if (temp->nim == nim && temp->bookId == bookId && !temp->isReturned)
      {
        temp->isReturned = true;
        temp->returnDate = getCurrentDate();
        cout << "Pengembalian buku " << bookId << " oleh " << nim << " tercatat.\n";
        return;
      }
      temp = temp->next;
    }
    cout << "Record peminjaman tidak ditemukan.\n";
  }

  void displayUserHistory(string nim)
  {
    if (!head)
    {
      cout << "Riwayat peminjaman kosong.\n";
      return;
    }

    cout << "\n=== Riwayat Peminjaman " << nim << " ===\n";
    BorrowRecord *temp = head;
    int count = 1;
    bool found = false;

    while (temp)
    {
      if (temp->nim == nim)
      {
        cout << count << ". Buku ID: " << temp->bookId
             << ", Tgl Pinjam: " << temp->borrowDate;
        if (temp->isReturned)
        {
          cout << ", Tgl Kembali: " << temp->returnDate << " (Sudah dikembalikan)";
        }
        else
        {
          cout << " (Belum dikembalikan)";
        }
        cout << "\n";
        found = true;
        count++;
      }
      temp = temp->next;
    }

    if (!found)
    {
      cout << "Tidak ada riwayat peminjaman untuk NIM " << nim << "\n";
    }
  }

  void displayAllHistory()
  {
    if (!head)
    {
      cout << "Riwayat peminjaman kosong.\n";
      return;
    }

    cout << "\n=== Semua Riwayat Peminjaman ===\n";
    BorrowRecord *temp = head;
    int count = 1;
    while (temp)
    {
      cout << count << ". NIM: " << temp->nim
           << ", Buku ID: " << temp->bookId
           << ", Tgl Pinjam: " << temp->borrowDate;
      if (temp->isReturned)
      {
        cout << ", Tgl Kembali: " << temp->returnDate;
      }
      cout << "\n";
      temp = temp->next;
      count++;
    }
  }
};

// ===== ENHANCED CAMPUS NAVIGATION CLASS (Using Directed Graph) =====
class CampusNavigation
{
private:
  vector<vector<pair<int, int>>> adjList; // adjacency list with weights
  vector<string> locationNames;
  vector<vector<int>> adjMatrix; // for displaying connections
  int numLocations;

public:
  CampusNavigation(int size) : numLocations(size)
  {
    adjList.resize(size);
    adjMatrix.resize(size, vector<int>(size, 0));
    locationNames.resize(size);
  }

  void addLocation(string location, int index)
  {
    if (index < numLocations)
    {
      locationNames[index] = location;
    }
  }

  void addDirectedPath(int from, int to, int distance)
  {
    adjList[from].push_back(make_pair(to, distance));
    adjMatrix[from][to] = distance;
    cout << "Jalur dari " << locationNames[from]
         << " ke " << locationNames[to]
         << " (jarak: " << distance << "m) ditambahkan.\n";
  }

  void addUndirectedPath(int location1, int location2, int distance)
  {
    addDirectedPath(location1, location2, distance);
    addDirectedPath(location2, location1, distance);
  }

  void displayConnections()
  {
    cout << "\n=== Peta Navigasi Kampus ===\n";
    for (int i = 0; i < numLocations; i++)
    {
      cout << locationNames[i] << " terhubung ke: ";
      for (auto &edge : adjList[i])
      {
        cout << locationNames[edge.first] << "(" << edge.second << "m) ";
      }
      cout << "\n";
    }
  }

  void findShortestPath(int start, int end)
  {
    vector<int> dist(numLocations, INT_MAX);
    vector<int> parent(numLocations, -1);
    vector<bool> visited(numLocations, false);

    dist[start] = 0;

    for (int count = 0; count < numLocations - 1; count++)
    {
      int u = -1;
      for (int v = 0; v < numLocations; v++)
      {
        if (!visited[v] && (u == -1 || dist[v] < dist[u]))
        {
          u = v;
        }
      }

      visited[u] = true;

      for (auto &edge : adjList[u])
      {
        int v = edge.first;
        int weight = edge.second;
        if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
          dist[v] = dist[u] + weight;
          parent[v] = u;
        }
      }
    }

    if (dist[end] == INT_MAX)
    {
      cout << "Tidak ada jalur dari " << locationNames[start]
           << " ke " << locationNames[end] << "\n";
      return;
    }

    cout << "\n=== Jalur Terpendek ===\n";
    cout << "Dari: " << locationNames[start] << "\n";
    cout << "Ke: " << locationNames[end] << "\n";
    cout << "Jarak total: " << dist[end] << "m\n";
    cout << "Rute: ";

    vector<int> path;
    int current = end;
    while (current != -1)
    {
      path.push_back(current);
      current = parent[current];
    }

    for (int i = path.size() - 1; i >= 0; i--)
    {
      cout << locationNames[path[i]];
      if (i > 0)
        cout << " -> ";
    }
    cout << "\n";
  }
};

// Now implement the exportToSorter function
void StudentList::exportToSorter(StudentSorter &sorter)
{
  Student *temp = head;
  while (temp)
  {
    sorter.addStudent(temp->name, temp->nim, temp->prodi);
    temp = temp->next;
  }
}

// ===== UTILITY FUNCTIONS =====

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
  int titleLen = static_cast<int>(title.length());
  int boxWidth = (titleLen + 6 > 30) ? (titleLen + 6) : 30;

  auto isSeparator = [](const std::string &s)
  {
    return s.find("=====") != std::string::npos || s == "";
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
    { // Arrow key
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
    { // Enter
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

// ===== MAIN FUNCTION =====
int main()
{
  // Initialize all system components
  StudentList list;
  ServiceQueue queue;
  TransactionStack stack;
  StudentHashTable hashTable;
  BST bst;
  StudentSorter sorter;

  // New SmartStudent components
  BookLibrary library;
  LoginSystem loginSystem;
  ActivityHistory activityHistory;
  BorrowingHistory borrowHistory;
  CampusNavigation campusNav(6);

  // Initialize campus locations
  campusNav.addLocation("Gerbang Utama", 0);
  campusNav.addLocation("Perpustakaan", 1);
  campusNav.addLocation("Gedung Informatika", 2);
  campusNav.addLocation("Gedung Manajemen", 3);
  campusNav.addLocation("Kantin", 4);
  campusNav.addLocation("Masjid", 5);

  // Add campus paths (undirected)
  campusNav.addUndirectedPath(0, 1, 100); // Gerbang -> Perpustakaan
  campusNav.addUndirectedPath(0, 4, 150); // Gerbang -> Kantin
  campusNav.addUndirectedPath(1, 2, 80);  // Perpustakaan -> Gedung Informatika
  campusNav.addUndirectedPath(1, 3, 120); // Perpustakaan -> Gedung Manajemen
  campusNav.addUndirectedPath(2, 5, 200); // Gedung Informatika -> Masjid
  campusNav.addUndirectedPath(3, 4, 90);  // Gedung Manajemen -> Kantin
  campusNav.addUndirectedPath(4, 5, 110); // Kantin -> Masjid

  // Initialize some sample data
  loginSystem.registerUser("220101", "pass123", "Ahmad Rizki");
  loginSystem.registerUser("220102", "pass456", "Sari Dewi");
  loginSystem.registerUser("220103", "pass789", "Budi Santoso");

  library.addBook("B001", "Algoritma dan Struktur Data", "Thomas Cormen", "Komputer");
  library.addBook("B002", "Database Systems", "Raghu Ramakrishnan", "Komputer");
  library.addBook("B003", "Manajemen Strategis", "Fred David", "Manajemen");
  library.addBook("B004", "Sistem Operasi", "Silberschatz", "Komputer");

  std::vector<std::string> menu = {
      "===== SISTEM LOGIN =====",
      "* Login",
      "* Register",
      "* Logout",
      "* Tampilkan Sesi Aktif",
      "",
      "===== PERPUSTAKAAN =====",
      "* Tampilkan Daftar Buku",
      "* Cari Buku",
      "* Pinjam Buku",
      "* Kembalikan Buku",
      "* Riwayat Peminjaman Saya",
      "",
      "===== KONSULTASI AKADEMIK =====",
      "* Daftar Antrian Konsultasi",
      "* Proses Antrian Konsultasi",
      "* Tampilkan Antrian",
      "",
      "===== RIWAYAT AKTIVITAS =====",
      "* Tampilkan Riwayat Aktivitas Saya",
      "* Tampilkan Semua Aktivitas",
      "",
      "===== NAVIGASI KAMPUS =====",
      "* Tampilkan Peta Kampus",
      "* Cari Jalur Terpendek",
      "* Tambah Jalur Baru",
      "",
      "===== DATA MAHASISWA =====",
      "* Tambah Mahasiswa",
      "* Tampilkan Daftar Mahasiswa",
      "* Hapus Mahasiswa",
      "",
      "===== PENCARIAN & SORTING =====",
      "* Urutkan Mahasiswa berdasarkan Nama",
      "* Urutkan Mahasiswa berdasarkan NIM",
      "* Cari Mahasiswa berdasarkan NIM",
      "* Cari Mahasiswa berdasarkan Nama",
      "",
      "===== SISTEM NILAI =====",
      "* Tambah Nilai ke BST",
      "* Tampilkan Data Nilai",
      "",
      "===== ADMINISTRASI =====",
      "* Hash Table Mahasiswa",
      "* Riwayat Transaksi",
      "* Undo Transaksi",
      "",
      "* Keluar"};

  int choice = 0;
  do
  {
    choice = interactiveMenu(menu, "SmartStudent - Sistem Layanan Mahasiswa Digital");
    clearScreen();

    std::string nim, name, prodi, service, transaction, password, bookId, keyword;
    int score, location1, location2, distance;
    std::vector<std::string> results;

    // Check if user needs to be logged in for certain operations
    bool needsLogin = (choice >= 5 && choice <= 9) || choice == 15 || choice == 16;
    if (needsLogin && !loginSystem.isLoggedIn())
    {
      cout << "Anda harus login terlebih dahulu untuk mengakses fitur ini!\n";
      cout << "Tekan apapun untuk kembali ke menu...";
      getch();
      continue;
    }

    switch (choice)
    {
    // ===== SISTEM LOGIN =====
    case 1: // Login
      clearScreen();
      cout << "==== Login SmartStudent ====" << endl;
      if (loginSystem.isLoggedIn())
      {
        cout << "Anda sudah login sebagai " << loginSystem.getCurrentUserName() << "\n";
      }
      else
      {
        inputForm({"NIM", "Password"}, results);
        if (!results.empty())
        {
          if (loginSystem.login(results[0], results[1]))
          {
            activityHistory.addActivity(results[0], "Login ke sistem");
          }
        }
      }
      break;

    case 2: // Register
      clearScreen();
      cout << "==== Register User Baru ====" << endl;
      inputForm({"NIM", "Password", "Nama Lengkap"}, results);
      if (!results.empty())
      {
        loginSystem.registerUser(results[0], results[1], results[2]);
      }
      break;

    case 3: // Logout
      clearScreen();
      cout << "==== Logout ====" << endl;
      if (loginSystem.isLoggedIn())
      {
        activityHistory.addActivity(loginSystem.getCurrentUser(), "Logout dari sistem");
        loginSystem.logout();
      }
      else
      {
        cout << "Anda belum login.\n";
      }
      break;

    case 4: // Tampilkan Sesi Aktif
      clearScreen();
      cout << "==== Informasi Sesi ====" << endl;
      loginSystem.displayCurrentSession();
      break;

    // ===== PERPUSTAKAAN =====
    case 7: // Tampilkan Daftar Buku
      clearScreen();
      cout << "==== Daftar Buku Perpustakaan ====" << endl;
      library.displayBooks();
      if (loginSystem.isLoggedIn())
      {
        activityHistory.addActivity(loginSystem.getCurrentUser(), "Melihat daftar buku");
      }
      break;

    case 8: // Cari Buku
      clearScreen();
      cout << "==== Pencarian Buku ====" << endl;
      inputForm({"Kata kunci (judul/pengarang/kategori)"}, results);
      if (!results.empty())
      {
        library.searchBooks(results[0]);
        if (loginSystem.isLoggedIn())
        {
          activityHistory.addActivity(loginSystem.getCurrentUser(), "Mencari buku: " + results[0]);
        }
      }
      break;

    case 9: // Pinjam Buku
      clearScreen();
      cout << "==== Pinjam Buku ====" << endl;
      inputForm({"ID Buku"}, results);
      if (!results.empty())
      {
        Book *book = library.findBookById(results[0]);
        if (book && book->isAvailable)
        {
          book->isAvailable = false;
          borrowHistory.borrowBook(loginSystem.getCurrentUser(), results[0]);
          activityHistory.addActivity(loginSystem.getCurrentUser(), "Meminjam buku: " + book->title);
        }
        else if (book)
        {
          cout << "Buku sedang dipinjam.\n";
        }
        else
        {
          cout << "Buku tidak ditemukan.\n";
        }
      }
      break;

    case 10: // Kembalikan Buku
      clearScreen();
      cout << "==== Kembalikan Buku ====" << endl;
      inputForm({"ID Buku"}, results);
      if (!results.empty())
      {
        Book *book = library.findBookById(results[0]);
        if (book && !book->isAvailable)
        {
          book->isAvailable = true;
          borrowHistory.returnBook(loginSystem.getCurrentUser(), results[0]);
          activityHistory.addActivity(loginSystem.getCurrentUser(), "Mengembalikan buku: " + book->title);
        }
        else if (book)
        {
          cout << "Buku tidak sedang dipinjam.\n";
        }
        else
        {
          cout << "Buku tidak ditemukan.\n";
        }
      }
      break;

    case 11: // Riwayat Peminjaman Saya
      clearScreen();
      cout << "==== Riwayat Peminjaman Saya ====" << endl;
      borrowHistory.displayUserHistory(loginSystem.getCurrentUser());
      activityHistory.addActivity(loginSystem.getCurrentUser(), "Melihat riwayat peminjaman");
      break;

    // ===== KONSULTASI AKADEMIK =====
    case 14: // Daftar Antrian Konsultasi
      clearScreen();
      cout << "==== Daftar Antrian Konsultasi ====" << endl;
      if (loginSystem.isLoggedIn())
      {
        inputForm({"Jenis Konsultasi"}, results);
        if (!results.empty())
        {
          queue.enqueue(loginSystem.getCurrentUser(), results[0]);
          activityHistory.addActivity(loginSystem.getCurrentUser(), "Mendaftar antrian konsultasi: " + results[0]);
        }
      }
      break;

    case 15: // Proses Antrian Konsultasi
      clearScreen();
      cout << "==== Proses Antrian Konsultasi ====" << endl;
      queue.dequeue();
      break;

    case 16: // Tampilkan Antrian
      clearScreen();
      cout << "==== Daftar Antrian Konsultasi ====" << endl;
      queue.display();
      break;

    // ===== RIWAYAT AKTIVITAS =====
    case 19: // Tampilkan Riwayat Aktivitas Saya
      clearScreen();
      cout << "==== Riwayat Aktivitas Saya ====" << endl;
      if (loginSystem.isLoggedIn())
      {
        activityHistory.displayUserActivities(loginSystem.getCurrentUser());
      }
      break;

    case 20: // Tampilkan Semua Aktivitas
      clearScreen();
      cout << "==== Semua Riwayat Aktivitas ====" << endl;
      activityHistory.displayAllActivities();
      break;

    // ===== NAVIGASI KAMPUS =====
    case 23: // Tampilkan Peta Kampus
      clearScreen();
      cout << "==== Peta Navigasi Kampus ====" << endl;
      campusNav.displayConnections();
      if (loginSystem.isLoggedIn())
      {
        activityHistory.addActivity(loginSystem.getCurrentUser(), "Melihat peta kampus");
      }
      break;

    case 24: // Cari Jalur Terpendek
      clearScreen();
      cout << "==== Pencarian Jalur Terpendek ====" << endl;
      cout << "Lokasi: 0=Gerbang, 1=Perpustakaan, 2=Gedung Informatika, 3=Gedung Manajemen, 4=Kantin, 5=Masjid\n";
      inputForm({"Lokasi asal (0-5)", "Lokasi tujuan (0-5)"}, results);
      if (!results.empty())
      {
        location1 = stoi(results[0]);
        location2 = stoi(results[1]);
        campusNav.findShortestPath(location1, location2);
        if (loginSystem.isLoggedIn())
        {
          activityHistory.addActivity(loginSystem.getCurrentUser(), "Mencari jalur dari lokasi " + results[0] + " ke " + results[1]);
        }
      }
      break;

    case 25: // Tambah Jalur Baru
      clearScreen();
      cout << "==== Tambah Jalur Kampus Baru ====" << endl;
      cout << "Lokasi: 0=Gerbang, 1=Perpustakaan, 2=Gedung Informatika, 3=Gedung Manajemen, 4=Kantin, 5=Masjid\n";
      inputForm({"Lokasi 1 (0-5)", "Lokasi 2 (0-5)", "Jarak (meter)"}, results);
      if (!results.empty())
      {
        location1 = stoi(results[0]);
        location2 = stoi(results[1]);
        distance = stoi(results[2]);
        campusNav.addUndirectedPath(location1, location2, distance);
      }
      break;

    // ===== DATA MAHASISWA =====
    case 28: // Tambah Mahasiswa
      clearScreen();
      cout << "==== Tambah Mahasiswa ====" << endl;
      inputForm({"NIM", "Nama", "Prodi"}, results);
      if (!results.empty())
      {
        list.addStudent(results[0], results[1], results[2]);
        hashTable.insert(results[0], results[1], results[2]);
      }
      break;

    case 29: // Tampilkan Daftar Mahasiswa
      clearScreen();
      cout << "==== Daftar Mahasiswa ====" << endl;
      list.display();
      break;

    case 30: // Hapus Mahasiswa
      clearScreen();
      cout << "==== Hapus Mahasiswa ====" << endl;
      inputForm({"NIM yang akan dihapus"}, results);
      if (!results.empty())
      {
        list.deleteStudent(results[0]);
        hashTable.remove(results[0]);
      }
      break;

    // ===== PENCARIAN & SORTING =====
    case 33: // Urutkan Mahasiswa berdasarkan Nama
      clearScreen();
      cout << "==== Urutkan Mahasiswa berdasarkan Nama ====" << endl;
      sorter.clearData();
      list.exportToSorter(sorter);
      sorter.sortByName();
      break;

    case 34: // Urutkan Mahasiswa berdasarkan NIM
      clearScreen();
      cout << "==== Urutkan Mahasiswa berdasarkan NIM ====" << endl;
      sorter.clearData();
      list.exportToSorter(sorter);
      sorter.sortByNIM();
      break;

    case 35: // Cari Mahasiswa berdasarkan NIM
      clearScreen();
      cout << "==== Cari Mahasiswa berdasarkan NIM (Binary Search) ====" << endl;
      sorter.clearData();
      list.exportToSorter(sorter);
      inputForm({"NIM"}, results);
      if (!results.empty())
      {
        sorter.searchByNIM(results[0]);
      }
      break;

    case 36: // Cari Mahasiswa berdasarkan Nama
      clearScreen();
      cout << "==== Cari Mahasiswa berdasarkan Nama (Linear Search) ====" << endl;
      sorter.clearData();
      list.exportToSorter(sorter);
      inputForm({"Nama yang dicari"}, results);
      if (!results.empty())
      {
        sorter.linearSearchByName(results[0]);
      }
      break;

    // ===== SISTEM NILAI =====
    case 39: // Tambah Nilai ke BST
      clearScreen();
      cout << "==== Tambah Nilai ke BST ====" << endl;
      inputForm({"NIM", "Nilai"}, results);
      if (!results.empty())
      {
        score = stoi(results[1]);
        bst.insert(results[0], score);
      }
      break;

    case 40: // Tampilkan Data Nilai
      clearScreen();
      cout << "==== Data Nilai (BST) ====" << endl;
      bst.display();
      break;

    // ===== ADMINISTRASI =====
    case 43: // Hash Table Mahasiswa
      clearScreen();
      cout << "==== Hash Table Mahasiswa ====" << endl;
      hashTable.display();
      break;

    case 44: // Riwayat Transaksi
      clearScreen();
      cout << "==== Riwayat Transaksi ====" << endl;
      stack.display();
      break;

    case 45: // Undo Transaksi
      clearScreen();
      cout << "==== Undo Transaksi ====" << endl;
      stack.pop();
      break;

    case 47: // Exit
      clearScreen();
      cout << "Terima kasih telah menggunakan SmartStudent!\n";
      cout << "Sistem Layanan Mahasiswa Digital - Kampus Cakrawala\n";
      break;

    default:
      clearScreen();
      cout << "Pilihan tidak valid.\n";
    }

    if (choice != 47)
    {
      cout << "\nTekan apapun untuk kembali ke menu...";
      getch();
    }
  } while (choice != 47);

  return 0;
}
