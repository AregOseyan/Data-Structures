#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <cassert>

template <typename T, size_t s>
class Array
{
  public:
    template <typename E, size_t si>
    friend std::ostream& operator<<(std::ostream& os, const Array<E, si>& ar);
  public:
    struct Iterator
    {
      using iterator_category = std::contiguous_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = T;
      using pointer = T*;
      using reference = T&;

      Iterator(pointer ptr)
        : m_ptr(ptr)
      { }

      reference operator*() const
      {
        return *m_ptr;
      }
      pointer operator->()
      {
        return m_ptr;
      }
      Iterator& operator++()
      {
        m_ptr++;
        return *this;
      }
      Iterator operator++(int)
      {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
      }
      Iterator operator+=(int idx)
      {
        m_ptr = m_ptr + idx;
        return *this;
      }

      friend bool operator== (const Iterator& a, const Iterator& b)
      {
        return a.m_ptr == b.m_ptr;
      };

      friend bool operator!= (const Iterator& a, const Iterator& b)
      {
        return a.m_ptr != b.m_ptr;
      };

      private:
        pointer m_ptr;
    };
  public:
    Array();
    Array(Array const& oldArr);
    Array(Array&& oldArr);
    Array(std::initializer_list<T> l);
  public:
    bool empty() const;
    size_t getSize() const;
    size_t maxSize() const;
    void fill(T item);
    void swap();

  public:
    Array& operator=(Array const& arr1);
    bool operator!= (Array const& arr1);
    bool operator<(Array const& arr1);
    bool operator<=(Array const& arr1);
    bool operator>(Array const& arr1);
    bool operator>=(Array const& arr1);
    bool operator==(Array const& arr1);

    T const& operator[] (unsigned int idx) const;
    T& operator[] (unsigned int idx);

    Iterator begin()
    {
      return Iterator(&m_arr[0]);
    }

    Iterator end()
    {
      return Iterator(&m_arr[m_size]);
    }

    Iterator rbegin()
    {
      return Iterator(&m_arr[m_size]);
    }

    Iterator rend()
    {
      return Iterator(&m_arr[0]);
    }

  private:
    T m_arr[s];
    int m_size;
};

template <typename E, size_t si>
std::ostream& operator<<(std::ostream& os, const Array<E, si>& ar)
{
  for (int i = 0; i < ar.m_size; ++i)
    os << ar.m_arr[i] << " ";
  os << std::endl;
  return os;
}

template <typename T, size_t s>
Array<T, s>::Array()
  : m_size(0)
{
  for (int j = 0; j < s; ++j) { m_arr[j] = {}; }
}

template <typename T, size_t s>
Array<T, s>::Array(Array const& oldArr)
{
  int tmp[s];
  for (int j = 0; j < s; ++j) { tmp[j] = {}; }
  for (int i = 0; i < oldArr.m_size; ++i) 
  {
    tmp[i] = oldArr[i];
  }
  m_arr = tmp;
  m_size = oldArr.m_size;
}

template <typename T, size_t s>
Array<T, s>::Array(Array&& oldArr)
  : m_arr(oldArr.m_arr)
  , m_size(oldArr.m_size)
{ 
  oldArr.m_arr = {};
  oldArr.m_size = {};
}
template <typename T, size_t s>
Array<T, s>::Array(std::initializer_list<T> l)
{
  for (int j = 0; j < s; ++j) { m_arr[j] = {}; }
  int i = 0;
  for (auto item : l)
  {
    m_arr[i] = item;
    i++;
  }
  m_size = l.size();
}

template <typename T, size_t s>
T& Array<T, s>::operator[] (unsigned int idx)
{
  assert(idx >= 0 && idx < s);
  return *(m_arr + idx);
}

template <typename T, size_t s>
T const& Array<T, s>::operator[](unsigned int idx) const
{
  assert(idx >= 0 && idx < s);
  return *(m_arr + idx);
}

template <typename T, size_t s>
bool Array<T, s>::empty() const
{
  return m_size == 0 ? true : false;
}

template <typename T, size_t s>
size_t Array<T, s>::getSize() const
{
  return m_size;
}

template <typename T, size_t s>
size_t Array<T, s>::maxSize() const
{
  return s;
}

template <typename T, size_t s>
void Array<T, s>::fill(T item)
{
  for (int i = 0; i < s; ++i) { m_arr[i] = item; }
}

template <typename T, size_t s>
void Array<T, s>::swap()
{
  int end = m_size - 1;
  for (int i = 0; i < m_size / 2; ++i) 
  { 
    std::swap(m_arr[i], m_arr[end]);
    end--;
  } 
}

template <typename T, size_t s>
bool Array<T, s>::operator!= (Array const& arr1)
{
  return !(m_arr == arr1);
}

template <typename T, size_t s>
bool Array<T, s>::operator<(Array const& arr1)
{
  return !(m_arr > arr1);
}

template <typename T, size_t s>
bool Array<T, s>::operator<=(Array const& arr1)
{
  return ((m_arr == arr1) || (m_arr < arr1)); 
}

template <typename T, size_t s>
bool Array<T, s>::operator>(Array const& arr1)
{
  if (arr1.maxSize() > m_arr.maxSize()) return false;
  if (arr1.maxSize() < m_arr.maxSize()) return true;
  for (int i = 0; i < arr1.maxSize(); ++i)
  {
    if (arr1[i] > m_arr[i]) { return false; }
  }
  return true;
}

template <typename T, size_t s>
bool Array<T, s>::operator>=(Array const& arr1)
{
  return ((m_arr == arr1) || (m_arr > arr1));
}

template <typename T, size_t s>
bool Array<T, s>::operator== (Array const& arr1)
{
  if (arr1.maxSize() != this->maxSize()) return false;
  for (int i = 0; i < this->maxSize(); ++i)
  {
    if (arr1[i] != m_arr[i]) { return false; }
  }
  return true;
}

template <typename T, size_t s>
Array<T, s>& Array<T, s>::operator=(Array const& arr1)
{
  if (this = &arr1) { return *this; }
  int tmp[s];
  for (int j = 0; j < s; ++j) { tmp[j] = {}; }
  for (int i = 0; i < arr1.m_size; ++i)
  {
    tmp[i] = arr1[i];
  }
  m_arr = tmp;
  m_size = arr1.m_size;
  return *this;
}

#endif // ARRAY_HPP
