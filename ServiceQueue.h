#ifndef SERVICEQUEUE_H
#define SERVICEQUEUE_H

#include <iostream>
#include <string>

using namespace std;

class ServiceQueue
{
private:
  struct Node
  {
    string nim, service;
    Node *next;
    Node(string _nim, string _service) : nim(_nim), service(_service), next(nullptr) {}
  };
  Node *front;
  Node *rear;
  int size;

public:
  ServiceQueue() : front(nullptr), rear(nullptr), size(0) {}

  // Destructor untuk memory management
  ~ServiceQueue()
  {
    while (front)
    {
      Node *temp = front;
      front = front->next;
      delete temp;
    }
  }

  void enqueue(string nim, string service);
  void dequeue();
  void display();
  int getSize();
};

#endif
