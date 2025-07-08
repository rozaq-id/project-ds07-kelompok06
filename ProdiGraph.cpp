#include "ProdiGraph.h"

ProdiGraph::ProdiGraph(int size)
{
  adjMatrix.resize(size, vector<int>(size, 0));
  prodiList.resize(size);
}

void ProdiGraph::addProdi(string prodi, int index)
{
  prodiList[index] = prodi;
}

void ProdiGraph::addEdge(int i, int j)
{
  adjMatrix[i][j] = 1;
  adjMatrix[j][i] = 1;
  cout << "Hubungan antara " << prodiList[i] << " dan " << prodiList[j] << " ditambahkan.\n";
}

void ProdiGraph::display()
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
