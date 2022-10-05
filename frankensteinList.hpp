#ifndef FRANKENSTEIN_LIST_HPP
#define FRANKENSTEIN_LIST_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class FList
{
  public:
    template <typename E>
    friend std::ostream& operator<<(std::ostream&, const FList<E>&);

    FList();

  private:
    struct Node
    {
      T data;
      Node* next;
      Node* prev;
      Node* asc;
      Node* desc;
      Node();
      Node(T val, Node* n = nullptr, Node* p = nullptr, Node* a = nullptr, Node* d = nullptr);
    };

  public:
    void push_front(T val);
    void push_back(T val);
    void insert(T val, int pos);
    void putSorted(Node* n);
    void printSorted() const;

    int getSize() const;
  private:
    Node* m_head;
    Node* m_tail;
    Node* m_asc;
    Node* m_desc;
};

template <typename T>
FList<T>::Node::Node(T val, Node* n, Node* p, Node* a, Node* d)
  : data(val),
    next(n),
    prev(p),
    asc(a),
    desc(d)
{ }

template <typename T>
FList<T>::Node::Node()
  : data(0),
    next(nullptr),
    prev(nullptr),
    asc(nullptr),
    desc(nullptr)
{ }

template <typename T>
FList<T>::FList()
  : m_head(nullptr),
    m_tail(nullptr),
    m_asc(nullptr),
    m_desc(nullptr)
{ }

template <typename T>
std::ostream& operator<<(std::ostream& os, const FList<T>& list)
{
  auto curr = list.m_head;
  while (curr)
  {
    os << curr->data << " ";
    curr = curr->next;
  }
  return os;
}

template <typename T>
int FList<T>::getSize() const
{
  size_t res = 0;
  Node* curr = m_head;
  while (curr != nullptr)
  {
    res++;
    curr = curr->next;
  }
  return res;
}

template <typename T>
void FList<T>::putSorted(Node* n)
{
  if (m_asc == nullptr)
  {
    m_asc = n;
    m_desc = n;
    return;
  }
  if (m_asc->data <= n->data)
  {
    Node* tmp = m_asc;
    m_asc->asc = n;
    m_asc = n;
    n->desc = tmp;
    return;
  }
  else if (m_desc->data >= n->data)
  {
    Node* tmp = m_desc;
    m_desc->desc = n;
    m_desc = n;
    n->asc = tmp;
    return;
  }
  else
  {
    Node* curr = m_asc;
    Node* tmp;
    while (curr != nullptr && (curr->data > n->data))
    {
      tmp = curr;
      curr = curr->desc;
    }
    tmp->desc = n;
    n->desc = curr;
    n->asc = tmp;
    curr->asc = n;
  }
}

template <typename T>
void FList<T>::push_front(T val)
{
  Node* newNode = new Node(val);
  if (m_head == nullptr)
  {
    m_head = newNode;
    m_tail = newNode;
    putSorted(newNode);
    return;
  }
  newNode->next = m_head;
  m_head->prev = newNode;
  newNode->prev = nullptr;
  m_head = newNode;

  putSorted(newNode);
}

template <typename T>
void FList<T>::push_back(T val)
{
  Node* newNode = new Node(val);
  if (m_tail == nullptr)
  {
    m_head = newNode;
    m_tail = newNode;
    putSorted(newNode);
    return;
  }
  m_tail->next = newNode;
  newNode->next = nullptr;
  newNode->prev = m_tail;
  m_tail = newNode;

  putSorted(newNode);
}

template <typename T>
void FList<T>::printSorted() const
{
  auto curr = m_asc;
  while (curr)
  {
    std::cout << curr->data << " ";
    curr = curr->desc;
  }
  std::cout << std::endl;
}

template <typename T>
void FList<T>::insert(T val, int pos)
{
  if (pos < 0 || pos > getSize()) { throw std::invalid_argument( "Position Error!!!" ); }
  if (0 == pos) { push_front(val); }
  else if (pos == getSize()) { push_back(val); }
  else
  {
    Node* tmp;
    int count = 0;
    Node* curr = m_head;
    while (count != pos)
    {
      tmp = curr;
      curr = curr->next;
      count++;
    }
    Node* newNode = new Node(val);
    newNode->next = curr;
    newNode->prev = tmp;
    tmp->next = newNode;
    curr->prev = newNode;

    putSorted(newNode);
  }
}

#endif // FRANKENSTEIN_LIST_HPP 
