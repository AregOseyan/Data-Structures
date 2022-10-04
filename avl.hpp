#ifndef AVL_H
#define AVL_H

#include <queue>
#include <stack>
#include <iostream>
#include <limits>

template <typename T>
class avl
{
  public:
    avl();

    bool isEmpty() const;
    bool isBST() const;

    void insert(T item);
    void clear();
    void findKey(T key) const;

    void printInOrder() const;
    void printPreOrder() const;
    void printPostOrder() const;

    int getHeight() const;
    int getSize() const;
    int size() const;
    T min() const;
    T max() const;
    int width() const;
    T successor(T val) const;
    T predecessor(T val) const;

    void printInOrderWithStack() const;
    int getHeightWithStack() const;
    void del(T key);
  private:
    struct Node
    {
      T data;
      Node* left;
      Node* right;
      Node* parent;

      Node();
    };
  private:
    void clearPostOrder(Node* root);
    bool BST(Node* root) const;
    int height(Node* root) const;
    int sizeRec(Node* root) const;
    Node* getMax(Node* root) const;
    Node* getMin(Node* root) const;
    int heightWithStack(Node* root) const;
    int getWidth(Node* root) const;

    void inOrder(Node* root) const;
    void preOrder(Node* root) const;
    void postOrder(Node* root) const;
    void inOrderWithStack(Node* root) const;

    void leftRotate(Node* x);
    void rightRotate(Node* y);
    int difference(Node* root) const;
    void balance(Node* newNode);

    Node* getSuccessor(Node* root, T val) const;
    Node* getPredecessor(Node* root, T val) const;
    Node* find(Node* root, T key) const;
  private:
    Node* m_root;
    int m_size;
};

template <typename T>
avl<T>::avl()
  : m_root{nullptr},
    m_size{0}
{ }

template <typename T>
avl<T>::Node::Node()
{
  data = 0;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

template <typename T>
void avl<T>::clearPostOrder(Node* root)
{
  if (root != nullptr)
  {
    clearPostOrder(root->left);
    clearPostOrder(root->right);
    delete root;
  }
}

template <typename T>
void avl<T>::clear()
{
  clearPostOrder(m_root);
  std::cout << "The tree was cleared\n";
}

template <typename T>
bool avl<T>::isEmpty() const 
{ 
  return m_root == nullptr; 
}

template <typename T>
void avl<T>::insert(T item)
{
  Node* newNode = new Node;
  newNode->data = item;
  m_size++;
  if (m_root == nullptr) { m_root = newNode; }
  else
  {
    Node* ptr = m_root;
    while (ptr != nullptr)
    {
      newNode->parent = ptr;
      if (item > ptr->data) { ptr = ptr->right; }
      else { ptr = ptr->left; }
    }
    if (item < newNode->parent->data) 
    { 
      newNode->parent->left = newNode;
    }
    else 
    { 
      newNode->parent->right = newNode;
    }
    balance(newNode->parent);
  }
}

template <typename T>
void avl<T>::inOrder(Node* root) const
{
  if (!root) { return; }
  inOrder(root->left);
  std::cout << root->data << "\t";
  inOrder(root->right);
}

template <typename T>
void avl<T>::printInOrder() const 
{ 
  inOrder(m_root); 
}

template <typename T>
void avl<T>::preOrder(Node* root) const
{
  if (!root) { return; }
  std::cout << root->data << "\t";
  preOrder(root->left);
  preOrder(root->right);
}

template <typename T>
void avl<T>::printPreOrder() const 
{ 
  preOrder(m_root); 
}

template <typename T>
void avl<T>::postOrder(Node* root) const
{
  if (!root) { return; }
  postOrder(root->left);
  postOrder(root->right);
  std::cout << root->data << "\t";
}

template <typename T>
void avl<T>::printPostOrder() const 
{ 
  postOrder(m_root); 
}

template <typename T>
int avl<T>::getSize() const 
{ 
  return m_size; 
}

template <typename T>
typename avl<T>::Node* avl<T>::find(Node* root, T key) const
{
  if (!root) { return nullptr; }
  else if (root->data == key) { return root; }
  else if (root->data > key) { return find(root->left, key); }
  else { return find(root->right, key); }
}

template <typename T>
int avl<T>::difference(Node* root) const
{
  return height(root->left) - height(root->right); 
}

template <typename T>
void avl<T>::balance(Node* newNode)
{
  while (newNode)
  {
    int balFactor = difference(newNode);
    if (balFactor > 1)
    {
      if (!newNode->left->left)
      {
        leftRotate(newNode->left); 
      }
      rightRotate(newNode);
    }
    else if (balFactor < -1)
    {
      if (!newNode->right->right)
      {
        rightRotate(newNode->right);
      }
      leftRotate(newNode); 
    }
    newNode = newNode->parent;
  }
}

template <typename T>
void avl<T>::findKey(T key) const
{
  Node* tmp = find(m_root, key);
  if (tmp) { std::cout << "Element exists in tree\n"; }
  else { std::cout << "Element not found in tree!!!\n"; }
}

template <typename T>
int avl<T>::sizeRec(Node* root) const
{
  if (!root) { return 0; }
  return (sizeRec(root->left) + sizeRec(root->right) + 1);
}

template <typename T>
int avl<T>::size() const 
{ 
  return sizeRec(m_root); 
}

template <typename T>
typename avl<T>::Node* avl<T>::getMin(Node* root) const
{
  if (root == nullptr) { return nullptr; }
  if (root->left == nullptr) { return root; }
  return getMin(root->left);
}

template <typename T>
T avl<T>::min() const 
{
  Node* tmp = getMin(m_root);
  if(!tmp) { return std::numeric_limits<T>::min(); }
  return tmp->data;
}

template <typename T>
typename avl<T>::Node* avl<T>::getMax(Node* root) const
{
  if (root == nullptr) { return nullptr; }
  if (root->right == nullptr) { return root; }
  return getMax(root->right);
}

template <typename T>
T avl<T>::max() const 
{
  Node* tmp = getMax(m_root);
  if(!tmp) { return std::numeric_limits<T>::min(); }
  return tmp->data;
}

template <typename T>
int avl<T>::height(Node* root) const
{
  if (!root) { return 0; }
  return 1 + std::max(height(root->left), height(root->right));
}

template <typename T>
int avl<T>::getHeight() const 
{ 
  return height(m_root); 
}

template <typename T>
bool avl<T>::BST(Node* root) const
{
  std::stack<Node*> helper;
  Node* curr = root;
  int tmp = std::numeric_limits<T>::min();
  while (curr != nullptr || !helper.empty())
  {
    while (curr != nullptr)
    {
      helper.push(curr);
      curr = curr->left;
    }
    curr = helper.top();
    helper.pop();
    if (tmp > curr->data) { return false; }
    tmp = curr->data;
    curr = curr->right;
  }
  return true;
}

template <typename T>
bool avl<T>::isBST() const 
{ 
  return BST(m_root); 
}

template <typename T>
void avl<T>::del(T key)
{
  Node* dl = find(m_root, key);
  if (!dl->left && !dl->right)
  {
    if (dl->parent->data > dl->data) { dl->parent->left = nullptr; }
    else { dl->parent->right = nullptr; }
    delete dl;
    dl = nullptr;
  }
  else if ((!dl->left && dl->right) || (dl->left && dl->right))
  {
    Node* minRight = getMin(dl->right);
    T tmp = dl->data;
    dl->data = minRight->data;
    minRight->data = tmp;

    if (minRight->parent->data > dl->data) { minRight->parent->left = nullptr; }
    else { minRight->parent->right = nullptr; }
    delete minRight;
    minRight = nullptr;
  }
  else if (dl->left && !dl->right)
  {
    Node* minRight = getMax(dl->left);
    T tmp = dl->data;
    dl->data = minRight->data;
    minRight->data = tmp;

    if (minRight->parent->data > dl->data) { minRight->parent->left = nullptr; }
    else { minRight->parent->right = nullptr; }
    delete minRight;
    minRight = nullptr;
  }
}

template <typename T>
void avl<T>::inOrderWithStack(Node* root) const
{
  std::stack<Node*> helper; 
  Node* curr = root; 
  while (curr != nullptr || !helper.empty()) 
  { 
    while (curr != nullptr) 
    { 
      helper.push(curr); 
      curr = curr->left; 
    } 
    curr = helper.top(); 
    helper.pop();
    std::cout << curr->data << "\t";
    curr = curr->right;
  }
}

template <typename T>
void avl<T>::printInOrderWithStack() const 
{ 
  inOrderWithStack(m_root); 
}

template <typename T>
int avl<T>::heightWithStack(Node* root) const
{
  int result = 1;
  int count = 1;
  std::stack<Node*> helper;
  Node* curr = root;
  while (curr != nullptr || !helper.empty())
  {
    while (curr != nullptr)
    {
      helper.push(curr);
      curr = curr->left;
      count++;
    }
    curr = helper.top();
    helper.pop();
    if (curr->right == nullptr && count > result) { result = count; }
    curr = curr->right;
    count = 2;
  }
  return result;
}

template <typename T>
int avl<T>::getHeightWithStack() const
{
  return heightWithStack(m_root);
}

template <typename T>
int avl<T>::getWidth(Node* root) const
{
  std::queue<Node*> counter;
  counter.push(root);
  int result = std::numeric_limits<int>::min();
  while (!counter.empty())
  {
    if (result < int(counter.size())) { result = int(counter.size()); }
    size_t sz = counter.size();
    for (size_t i = 0; i < sz; ++i)
    {
      Node* tmp = counter.front();
      counter.pop();
      if (tmp->left) { counter.push(tmp->left); }
      if (tmp->right) { counter.push(tmp->right); }
    }
  }
  return result;
}

template <typename T>
int avl<T>::width() const
{
  return getWidth(m_root);
}

template <typename T>
void avl<T>::leftRotate(Node* x)
{
  Node* y = x->right;
  x->right = y->left;
  if (y->left != nullptr) { y->left->parent = x; }
  y->parent = x->parent;
  if (x->parent == nullptr) { m_root = y; }
  else if (x == x->parent->left) { x->parent->left = y; }
  else { x->parent->right = y; }
  y->left = x;
  x->parent = y;
}

template <typename T>
void avl<T>::rightRotate(Node* y)
{
  Node* x = y->left;
  y->left = x->right;
  if (x->right != nullptr) { x->right->parent = y; }
  x->parent = y->parent;
  if (y->parent == nullptr) { m_root = x; }
  else if (y == y->parent->left) { y->parent->left = x; }
  else { y->parent->right = x; }
  x->right = y;
  y->parent = x;
}

template <typename T>
typename avl<T>::Node* avl<T>::getSuccessor(Node* root, T val) const
{
  Node* current = find(root, val);
  if (!current) { return nullptr; }
  // Case 1
  if (current->right) { return getMin(current->right); }
  // Case 2
  else
  {
    Node* succ = nullptr;
    Node* ancestor = root;
    while(ancestor != current)
    {
      if(current->data < ancestor->data)
      {
        succ = ancestor;
        ancestor = ancestor->left;
      }
      else { ancestor = ancestor->right; }
    }
    return succ;
  }
}

template <typename T>
T avl<T>::successor(T val) const
{
  Node* tmp = getSuccessor(m_root, val);
  if(!tmp) { return std::numeric_limits<int>::min(); }
  return tmp->data;
}

template <typename T>
typename avl<T>::Node* avl<T>::getPredecessor(Node* root, T val) const
{
  Node* current = find(root, val);
  if (!current) { return nullptr; }
  // Case 1
  if (current->left) { return getMax(current->left); }
  // Case 2
  else
  {
    Node* prec = nullptr;
    Node* ancestor = root;
    while(ancestor != current)
    {
      if(current->data > ancestor->data)
      {
        prec = ancestor;
        ancestor = ancestor->right;
      }
      else { ancestor = ancestor->left; }
    }
    return prec;
  }
}

template <typename T>
T avl<T>::predecessor(T val) const
{
  Node* tmp = getPredecessor(m_root, val);
  if(!tmp) { return std::numeric_limits<int>::min(); }
  return tmp->data;
}

#endif // AVL_H
