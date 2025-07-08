#include "StudentList.h"
#include "StudentSorter.h"

void StudentList::addStudent(string nim, string name, string prodi)
{
  // Cek apakah NIM sudah ada
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

Student *StudentList::findByNIM(string nim)
{
  Student *temp = head;
  while (temp)
  {
    if (temp->nim == nim)
    {
      return temp;
    }
    temp = temp->next;
  }
  return nullptr;
}

void StudentList::deleteStudent(string nim)
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

void StudentList::display()
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

void StudentList::exportToSorter(StudentSorter &sorter)
{
  Student *temp = head;
  while (temp)
  {
    sorter.addStudent(temp->name, temp->nim, temp->prodi);
    temp = temp->next;
  }
}
