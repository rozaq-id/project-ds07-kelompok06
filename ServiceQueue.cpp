#include "ServiceQueue.h"

void ServiceQueue::enqueue(string nim, string service)
{
  Node *newNode = new Node(nim, service);
  if (!rear)
  {
    front = rear = newNode;
  }
  else
  {
    rear->next = newNode;
    rear = newNode;
  }
  size++;
  cout << "Antrian untuk " << nim << " (" << service << ") ditambahkan. Posisi: " << size << "\n";
}

void ServiceQueue::dequeue()
{
  if (!front)
  {
    cout << "Antrian kosong.\n";
    return;
  }
  Node *temp = front;
  cout << "Melayani " << temp->nim << " untuk " << temp->service << "\n";
  front = front->next;
  if (!front)
    rear = nullptr;
  delete temp;
  size--;
}

void ServiceQueue::display()
{
  if (!front)
  {
    cout << "Antrian kosong.\n";
    return;
  }

  cout << "\n=== Antrian Layanan ===\n";
  Node *temp = front;
  int pos = 1;
  while (temp)
  {
    cout << pos << ". NIM: " << temp->nim << " - Layanan: " << temp->service << "\n";
    temp = temp->next;
    pos++;
  }
  cout << "Total antrian: " << size << "\n";
}

int ServiceQueue::getSize()
{
  return size;
}
