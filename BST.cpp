#include "BST.h"

BST::Node *BST::insert(Node *node, string nim, int score)
{
  if (!node)
    return new Node(nim, score);
  if (score < node->score)
    node->left = insert(node->left, nim, score);
  else
    node->right = insert(node->right, nim, score);
  return node;
}

void BST::inOrder(Node *node)
{
  if (node)
  {
    inOrder(node->left);
    cout << "NIM: " << node->nim << ", Nilai: " << node->score << "\n";
    inOrder(node->right);
  }
}

void BST::insert(string nim, int score)
{
  root = insert(root, nim, score);
  cout << "Nilai " << score << " untuk " << nim << " ditambahkan ke BST.\n";
}

void BST::display()
{
  if (!root)
  {
    cout << "BST kosong.\n";
    return;
  }
  cout << "\n=== Data Nilai (In-Order) ===\n";
  inOrder(root);
}
