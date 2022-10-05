#ifndef STRING_HPP
#define STRING_HPP
#include <iostream>
#include <cstring>
#include <iterator>

class string
{
  friend std::ostream& operator<<(std::ostream& os, const string& str);
  friend std::istream& operator>>(std::istream& is, string& str);

public:
    struct Iterator
    {
      using iterator_category = std::random_access_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = char;
      using pointer = char*;
      using reference = char&;

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

    template <typename Itr>
    struct traits 
    {
      typedef typename Itr::difference_type diff_type;
      typedef typename Itr::value_type value_type;
      typedef typename Itr::iterator_category iterator_category;
      typedef typename Itr::pointer pointer;
      typedef typename Itr::reference reference;
    };

    template <typename T>
    struct traits<T*> 
    {
      typedef std::random_access_iterator_tag iterator_category;
      typedef T* value_type;
      typedef ptrdiff_t diff_type;
      typedef T* pointer;
      typedef T& reference;
    };

public:
  string();
  string(const char* str);
  string(const string& str);
  string(string&& str) noexcept;
  ~string();

  int length() const;
  int strlen(const char* str) const;
  void strcpy(char* str1, const char* str2);
  void resize(int newSize);
  int find(char ch) const;
  void push_back(char ch);
  void pop_back();
  bool empty() const;

  string& operator=(const string& str);
  string& operator=(const char* str);
  const char& operator[](int i) const;
  char& operator[](int i);
  bool operator<(const string& str) const;
  bool operator>(const string& str) const; 
  bool operator==(const string& str) const;
  string operator+(const string& str) const;

  Iterator begin()
  {
    return Iterator(&m_arr[0]);
  }

  Iterator end()
  {
    return Iterator(&m_arr[strlen(m_arr)]);
  }

  Iterator rbegin()
  {
    return Iterator(&m_arr[strlen(m_arr)]);
  }

  Iterator rend()
  {
    return Iterator(&m_arr[0]); 
  }

private:
  char* m_arr;
  int m_size = 0;
  static const int cinLim = 90;
};

int string::strlen(const char* str) const
{
  int len = 0;
  while (str[len] != '\0') { len++; }
  return len;
}

void string::strcpy(char* str1, const char* str2)
{
  int i = 0;
  while (*(str2 + i) != '\0')
  {
    *(str1 + i) = *(str2 + i);
    i++;
  }
  *(str1 + i) = '\0';
}

void string::resize(int newSize)
{
  int oldLength = m_size;
  char* oldArr = m_arr;

  m_size = newSize;
  m_arr = new char[m_size];

  for (int i = 0; i < m_size; ++i)
  {
    if (i < oldLength) { m_arr[i] = oldArr[i]; }
    else { m_arr[i] = '\0'; }
  }
  delete[] oldArr;
  m_arr[m_size] = '\0';
}

string::string()
{
  m_arr = new char[1];
  m_arr[0] = '\0';
}

string::string(const char* str)
{
  m_size = strlen(str);
  m_arr = new char[m_size + 1];
  strcpy(m_arr, str);
}

string::string(const string& str)
{
  m_size = str.m_size;
  m_arr = new char[m_size + 1];
  strcpy(m_arr, str.m_arr);
}

string::string(string&& str) noexcept
  : m_arr(std::move(str.m_arr))
  , m_size(std::move(str.m_size))
{ }

string::~string()
{
  delete[] m_arr;
}

int string::length() const
{
  return m_size;
}

int string::find(char ch) const
{
  for (int i = 0; i < m_size; ++i)
  {
    if (m_arr[i] == ch) { return i; }
  }
  return -1;
}

void string::push_back(char ch)
{
  char* temp = new char[m_size + 2];

  int i = 0;
  while(i != m_size)
  {
    temp[i] = m_arr[i];
    i++;
  }
  temp[i] = ch;
  i++;
  temp[i] = '\0';

  delete[] m_arr;
  m_arr = temp;
  m_size++;
}

void string::pop_back()
{
  if (m_size == 0) { return; }
  char* temp = new char[m_size];

  int i = 0;
  while (i != m_size - 1)
  {
    temp[i] = m_arr[i];
    i++;
  }
  temp[i] = '\0';

  delete[] m_arr;
  m_arr = temp;
  m_size--;
}

std::ostream& operator<<(std::ostream& os, const string& str)
{
  os << str.m_arr;
  return os;
}

std::istream& operator>>(std::istream& is, string& str)
{
  char temp[string::cinLim + 1];
  int i = 0;
  while (is && i < string::cinLim)
  {
    char s = is.get();
    if(s == '\n' || s == ' ') { break; }
    temp[i++] = s;
  }
  temp[i] = '\0';
  str = temp;

  return is;
}

char& string::operator[](int i)
{
  return m_arr[i];
}

const char& string::operator[](int i) const
{
  return m_arr[i];
}

bool string::empty() const
{
  return m_size == 0;
}

string& string::operator=(const string& str)
{
  if (this == &str) { return *this; }
  delete[] m_arr;
  m_size = str.m_size;
  m_arr = new char[m_size + 1];
  strcpy(m_arr, str.m_arr);

  return *this;
}

string& string::operator=(const char* str)
{
  delete[] m_arr;
  m_size = strlen(str);
  m_arr = new char[m_size + 1];
  strcpy(m_arr, str);

  return *this;
}

string string::operator+(const string& str) const
{
  string temp;
  delete[] temp.m_arr;
  temp.m_size = str.m_size + m_size;
  temp.m_arr = new char[temp.m_size + 1];

  int i = 0;
  for (int j = 0; (*this)[j] != '\0'; ++j)
  {
    temp[i++] = (*this)[j];
  }
  for (int j = 0; str[j] != '\0'; ++j)
  {
    temp[i++] = str[j];
  }
  temp[i] = '\0';

  return temp;
}

bool string::operator<(const string& str) const
{
  return (std::strcmp(str.m_arr, m_arr) < 0);
}

bool string::operator>(const string& str) const
{
  return str < *this;
}

bool string::operator==(const string& str) const
{
  return (std::strcmp(str.m_arr, m_arr) == 0);
}

#endif // STRING_HPP
