#ifndef HEAP_TRRE_HPP 
#define HEAP_TRRE_HPP
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

template <typename T>
struct heapTree
{
  heapTree(std::vector<T> vec);
  heapTree(heapTree&&) noexcept;

  int getLeft(int idx) const;
  int getRight(int idx) const;
  int getParent(int idx) const;
  int getHeight() const;

  void insert(T item);
  void print() const;
  void maxHeapify(int i);
  void buildMaxHeap();

  void maxHeapifySort(int idx, int size);
  void buildMaxHeapSort(int size); 
  void sort();

  heapTree& operator=(const heapTree& obj);
  bool operator==(heapTree<T> obj);

  std::vector<T> m_vec;
};

template <typename T>
heapTree<T>::heapTree(std::vector<T> vec)
{ 
  for (int i = 0; i < vec.size(); ++i) { m_vec.push_back(vec[i]); }
}

template <typename T>
heapTree<T>::heapTree(heapTree&& oth) noexcept 
      : m_vec(std::move(oth.m_arr))
{ }

template <typename T>
int heapTree<T>::getLeft(int idx) const
{
  // (index * 2) + 1
  return (idx * 2) + 1;
}

template <typename T>
int heapTree<T>::getRight(int idx) const
{
  // (index * 2) + 2
  return (idx * 2) + 2;
}

template <typename T>
int heapTree<T>::getParent(int idx) const
{
  // (index - 1) / 2
  return (idx - 1) / 2;
}

template <typename T>
int heapTree<T>::getHeight() const
{
  int count = 0;
  int i = 0;
  while (getLeft(i) < m_vec.size())
  {
    count++;
    i = getLeft(i);
  }
  return count + 1;
}

template <typename T>
void heapTree<T>::insert(T item)
{
  m_vec.push_back(item);
  buildMaxHeap();
}

template <typename T>
bool heapTree<T>::operator==(heapTree<T> obj)
{
  if (obj.size() != m_vec.size()) { return false; }
  for (int i = 0; i < obj.size(); ++i)
  {
    if (m_vec[i] != obj[i]) { return false; }
  }
  return true;
}

template <typename T>
heapTree<T>& heapTree<T>::operator=(const heapTree<T>& obj)
{
  if (this == &(obj)) { return *this; }
  for (int i = 0; i < obj.size(); ++i) { this->m_vec[i] = obj[i]; }
  return *this;
}

template <typename T>
void heapTree<T>::maxHeapify(int i)
{
  if (getLeft(i) < m_vec.size() && m_vec[i] < m_vec[getLeft(i)]) 
  {
    std::swap(m_vec[i], m_vec[getLeft(i)]);
  }
  if (m_vec.size() > getRight(i) && m_vec[i] < m_vec[getRight(i)]) 
  {
    std::swap(m_vec[i], m_vec[getRight(i)]);
  }
} 

template <typename T>
void heapTree<T>::buildMaxHeap()
{
  int j = getParent(m_vec.size() - 1);
  for (int i = j; i >= 0; --i) { maxHeapify(i); }
}

template <typename T>
void heapTree<T>::print() const
{
  for (int i = 0; i < m_vec.size(); ++i) { std::cout << m_vec[i] << " "; }
  std::cout << std::endl;
}

template <typename T>
void heapTree<T>::maxHeapifySort(int i, int size)
{
  if (getLeft(i) < size && m_vec[i] < m_vec[getLeft(i)])
  {
    std::swap(m_vec[i], m_vec[getLeft(i)]);
  }
  if (size > getRight(i) && m_vec[i] < m_vec[getRight(i)])
  {
    std::swap(m_vec[i], m_vec[getRight(i)]);
  }
}

template <typename T>
void heapTree<T>::buildMaxHeapSort(int size)
{
  int j = getParent(size - 1);
  for (int i = j; i >= 0; --i) { maxHeapify(i); }
}

template <typename T>
void heapTree<T>::sort()
{
  buildMaxHeap();
  int end = m_vec.size() - 1;
  for (int i = 0; i < m_vec.size(); ++i)
  {
    std::swap(m_vec[0], m_vec[end]);
    end--;
    buildMaxHeapSort(end);
  }
  //std::reverse(m_vec.begin(), m_vec.end());
}
#endif // HEAP_TRRE_HPP
