#include <iostream>
#include <string>
#include <vector>
#include <csignal>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <tuple>

// Platform-specific includes
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

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
    for (int i = 0; i < prodiList.size(); i++)
    {
      cout << prodiList[i] << ": ";
      for (int j = 0; j < prodiList.size(); j++)
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
    sort(students.begin(), students.end(), [](const auto &a, const auto &b)
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
    for (int i = 0; i < students.size(); i++)
    {
      cout << (i + 1) << ". Nama: " << get<0>(students[i])
           << ", NIM: " << get<1>(students[i])
           << ", Prodi: " << get<2>(students[i]) << "\n";
    }
  }

  void sortByNIM()
  {
    sort(students.begin(), students.end(), [](const auto &a, const auto &b)
         { return get<1>(a) < get<1>(b); });
    cout << "\n=== Daftar Mahasiswa (Urut NIM) ===\n";
    for (int i = 0; i < students.size(); i++)
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
    for (int i = 0; i < students.size(); i++)
    {
      cout << (i + 1) << ". Nama: " << get<0>(students[i])
           << ", NIM: " << get<1>(students[i])
           << ", Prodi: " << get<2>(students[i]) << "\n";
    }
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
