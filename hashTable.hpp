#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <forward_list>
#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include <limits>
#include <type_traits>

template <typename T>
class hashTable
{
  public:
    hashTable();
    hashTable(int s);

    void insert(T key);
    void del(T key);
    bool find(T key);
    void displayHash();
    int getSize() const;
    int getMaxSizeList();

  private:
    int getHashCode(T key);
    bool isPrime(int size) const;
    int nextPrimeNum(int s);
    bool m_flag = false;

  private:
    std::vector<std::forward_list<T>> m_table;
    int m_size;
};

template <typename T>
hashTable<T>::hashTable()
 : m_size(8),
   m_flag(true)
{
  m_table.resize(m_size);
}

template <typename T>
hashTable<T>::hashTable(int s)
 : m_size(s)
{
  m_table.resize(m_size);
}

template <typename T>
bool hashTable<T>::isPrime(int size) const
{
  if (size <= 1) { return false; }
  for (int i = 2; i < size; ++i)
  {
    if (size % i == 0) { return false; }
  }
  return true;
}

template <typename T>
int hashTable<T>::nextPrimeNum(int s)
{
  while (!isPrime(s)) { s++; }
  return s;
}

template <typename T>
void hashTable<T>::insert(T key)
{
  if (m_flag)
  {
    if (!find(key))
    {
      int k = getMaxSizeList(); 
      if ((m_size / 2) < k)
      {
        int hh = m_size;
        std::vector<std::forward_list<T>> tmp;
        m_size = m_size * 2;
        if (!isPrime(m_size)) { m_size = nextPrimeNum(m_size); }
        tmp.resize(m_size);

        for (int i = 0; i < hh; i++)
        {
          for (auto x : m_table[i]) 
          { 
            int index = getHashCode(x);
            tmp[index].push_front(x); 
          }
        }
        m_table = std::move(tmp);
      }
      int index = getHashCode(key);
      m_table[index].push_front(key);  
    }
  }

  else if (!find(key))
  {
    int index = getHashCode(key);
    m_table[index].push_front(key);
  } 
}

template <typename T>
int hashTable<T>::getSize() const
{
  return m_size;
}

template <typename T>
int hashTable<T>::getMaxSizeList()
{
  int res = std::numeric_limits<int>::min();
  for (int i = 0; i < m_size; i++)
  {
    int count = 0;
    for (auto x : m_table[i]) { count++; }
    if (res < count) { res = count; }
  }
  return res;
}

template <typename T>
int hashTable<T>::getHashCode(T key)
{
  if constexpr (std::is_integral<T>::value) { return (key % m_table.size()); }
  else
  {
    int hashPat = 0;
    for (int i = 0; i < key.size(); ++i)
    {
      hashPat = (hashPat * 10 + int(key[i])) % (key.size());
    }
    return hashPat;
  }
}

template <typename T>
bool hashTable<T>::find(T key)
{
  int index = getHashCode(key);

  typename std::forward_list<T>::iterator it;
  for (it = m_table[index].begin(); it != m_table[index].end(); ++it) 
  {
    if (*it == key) { return true; }
  }
  return false;
}

template <typename T>
void hashTable<T>::displayHash()
{
  for (int i = 0; i < m_size; i++) 
  { 
    for (auto x : m_table[i])
    {
      std::cout << x << " ";
    }
    std::cout << std::endl;
  }
}

template <typename T>
void hashTable<T>::del(T key)
{   
  int index = getHashCode(key);

  typename std::forward_list<T>::iterator it;
  for (it = m_table[index].begin(); it != m_table[index].end(); ++it)
  {
    if (*it == key) { break; }
  }
  if (it != m_table[index].end())
  {
    m_table[index].erase(it);
  } 
}

#endif // HASH_TABLE_HPP
