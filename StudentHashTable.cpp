#include "StudentHashTable.h"

void StudentHashTable::insert(string nim, string name, string prodi)
{
  table[nim] = make_pair(name, prodi);
  cout << "Data " << name << " disimpan di hash table.\n";
}

void StudentHashTable::search(string nim)
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

void StudentHashTable::remove(string nim)
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

void StudentHashTable::display()
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

int StudentHashTable::getSize()
{
  return table.size();
}
