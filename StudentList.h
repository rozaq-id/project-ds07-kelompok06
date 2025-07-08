#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "Student.h"

// Forward declaration
class StudentSorter;

class StudentList
{
private:
  Student *head;

public:
  StudentList() : head(nullptr) {}

  // Destructor untuk memory management
  ~StudentList()
  {
    while (head)
    {
      Student *temp = head;
      head = head->next;
      delete temp;
    }
  }

  void addStudent(string nim, string name, string prodi);
  Student *findByNIM(string nim);
  void deleteStudent(string nim);
  void display();
  void exportToSorter(StudentSorter &sorter); // Fungsi baru untuk ekspor data
};

#endif
