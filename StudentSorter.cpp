#include "StudentSorter.h"

void StudentSorter::addStudent(string name, string nim, string prodi)
{
  students.push_back(make_tuple(name, nim, prodi));
  cout << "Mahasiswa " << name << " ditambahkan ke sorter.\n";
}

void StudentSorter::sortByName()
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

void StudentSorter::sortByNIM()
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

void StudentSorter::searchByNIM(string nim)
{
  // Binary search (data harus terurut berdasarkan NIM)
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

void StudentSorter::linearSearchByName(string name)
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

void StudentSorter::display()
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

void StudentSorter::sortByNIMSilent()
{
  sort(students.begin(), students.end(), [](const auto &a, const auto &b)
       { return get<1>(a) < get<1>(b); });
}

void StudentSorter::clearData()
{
  students.clear();
}
