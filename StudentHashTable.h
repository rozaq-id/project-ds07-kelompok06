#ifndef STUDENTHASHTABLE_H
#define STUDENTHASHTABLE_H

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class StudentHashTable
{
private:
  unordered_map<string, pair<string, string>> table; // NIM -> {Nama, Prodi}

public:
  void insert(string nim, string name, string prodi);
  void search(string nim);
  void remove(string nim);
  void display();
  int getSize();
};

#endif
