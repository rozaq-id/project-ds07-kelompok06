#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

using namespace std;

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

  Node *insert(Node *node, string nim, int score);
  void inOrder(Node *node);

public:
  BST() : root(nullptr) {}
  void insert(string nim, int score);
  void display();
};

#endif
