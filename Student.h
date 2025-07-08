#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

// Struktur dasar untuk mahasiswa
struct Student
{
  string nim, name, prodi;
  Student *next;
  Student(string _nim, string _name, string _prodi) : nim(_nim), name(_name), prodi(_prodi), next(nullptr) {}
};

#endif
