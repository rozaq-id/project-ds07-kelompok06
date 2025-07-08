#ifndef PRODIGRAPH_H
#define PRODIGRAPH_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ProdiGraph
{
private:
  vector<vector<int>> adjMatrix;
  vector<string> prodiList;

public:
  ProdiGraph(int size);
  void addProdi(string prodi, int index);
  void addEdge(int i, int j);
  void display();
};

#endif
