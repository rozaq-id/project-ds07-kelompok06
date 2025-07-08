#ifndef TRANSACTIONSTACK_H
#define TRANSACTIONSTACK_H

#include <iostream>
#include <string>

using namespace std;

class TransactionStack
{
private:
  struct Node
  {
    string transaction;
    string timestamp;
    Node *next;
    Node(string _transaction, string _timestamp) : transaction(_transaction), timestamp(_timestamp), next(nullptr) {}
  };
  Node *top;
  int size;

public:
  TransactionStack() : top(nullptr), size(0) {}

  // Destructor untuk memory management
  ~TransactionStack()
  {
    while (top)
    {
      Node *temp = top;
      top = top->next;
      delete temp;
    }
  }

  string getCurrentTime();
  void push(string transaction);
  void pop();
  void display();
  int getSize();
};

#endif
