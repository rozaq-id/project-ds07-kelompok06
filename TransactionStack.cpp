#include "TransactionStack.h"

string TransactionStack::getCurrentTime()
{
  // Simplified timestamp
  return "2025-07-08 10:00:00";
}

void TransactionStack::push(string transaction)
{
  Node *newNode = new Node(transaction, getCurrentTime());
  newNode->next = top;
  top = newNode;
  size++;
  cout << "Transaksi: " << transaction << " dicatat pada " << newNode->timestamp << "\n";
}

void TransactionStack::pop()
{
  if (!top)
  {
    cout << "Riwayat transaksi kosong.\n";
    return;
  }
  Node *temp = top;
  cout << "Undo transaksi: " << temp->transaction << " (pada " << temp->timestamp << ")\n";
  top = top->next;
  delete temp;
  size--;
}

void TransactionStack::display()
{
  if (!top)
  {
    cout << "Riwayat transaksi kosong.\n";
    return;
  }

  cout << "\n=== Riwayat Transaksi ===\n";
  Node *temp = top;
  int count = 1;
  while (temp)
  {
    cout << count << ". " << temp->transaction << " (pada " << temp->timestamp << ")\n";
    temp = temp->next;
    count++;
  }
  cout << "Total transaksi: " << size << "\n";
}

int TransactionStack::getSize()
{
  return size;
}
