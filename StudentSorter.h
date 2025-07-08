#ifndef STUDENTSORTER_H
#define STUDENTSORTER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class StudentSorter
{
private:
  vector<tuple<string, string, string>> students; // Nama, NIM, Prodi
  void sortByNIMSilent();

public:
  void addStudent(string name, string nim, string prodi);
  void clearData(); // Fungsi baru untuk clear data
  void sortByName();
  void sortByNIM();
  void searchByNIM(string nim);
  void linearSearchByName(string name);
  void display();
};

#endif
