#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>

template <typename E, typename F>
struct pair
{
  public:
    E m_first;
    F m_second;

  public:
    template <typename T1, typename T2>
    friend std::ostream& operator<<(std::ostream&, const pair<T1, T2>&);

    pair() = default;
    pair(E val1, F val2);
    pair(const pair& other);
    pair(pair&& other) noexcept;
    ~pair() = default;

    bool operator==(const pair<E, F>& other);
    bool operator!=(const pair<E, F>& other);
    bool operator<(const pair<E, F>& other);
    bool operator<=(const pair<E, F>& other);
    bool operator>(const pair<E, F>& other);
    bool operator>=(const pair<E, F>& other);

    pair& operator=(const pair& other);
    pair& operator=(pair&& other) noexcept;
    void swap(pair& other) noexcept;
    
    pair make_pair(E t, F u);
};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const pair<T1, T2>& pa)
{
  os << "(" << pa.m_first << ", " << pa.m_second << ")" << "\n";
  return os;
}

template <typename E, typename F>
pair<E, F>::pair(E val1, F val2)
  : m_first(val1),
    m_second(val2) 
{ }

template <typename E, typename F>
pair<E, F>::pair(const pair& other)
{
  operator=(other);
}

template <typename E, typename F>
pair<E, F>::pair(pair&& other) noexcept
  : m_first(std::move(other.m_first)),
	  m_second(std::move(other.m_second))
{ } 

template <typename E, typename F>
pair<E, F>& pair<E, F>::operator=(const pair& other)
{
	if (&other != this) 
  {
		m_first = other.m_first;
		m_second = other.m_second;
	}
	return *this;
}

template <typename E, typename F>
pair<E, F>& pair<E, F>::operator=(pair&& other) noexcept
{
  m_first = std::move(other.m_first);
	m_second = std::move(other.m_second);
	return *this;
}

template<typename E, typename F>
bool pair<E, F>::operator==(const pair<E, F>& other)
{
  return ((m_first == other.m_first) && (m_second == other.m_second));  
}

template<typename E, typename F>
bool pair<E, F>::operator!=(const pair<E, F>& other)
{
  return !operator==(other);
}

template<typename E, typename F>
bool pair<E, F>::operator<(const pair<E, F>& other)
{
  return ((m_first < other.m_first) && (m_second < other.m_second));
}

template<typename E, typename F>
bool pair<E, F>::operator>(const pair<E, F>& other)
{
  return !operator<(other);
}

template<typename E, typename F>
bool pair<E, F>::operator<=(const pair<E, F>& other)
{
  return operator<(other) || operator==(other);  
}

template<typename E, typename F>
bool pair<E, F>::operator>=(const pair<E, F>& other)
{
  return operator>(other) || operator==(other);
}

template<typename E, typename F>
void pair<E, F>::swap(pair& other) noexcept
{
  F tmp2 = m_second;
  m_second = other.m_second;  
  other.m_second = tmp2;

  E tmp1 = m_first;
  m_first = other.m_first;
  other.m_first = tmp1;
}

template <typename E, typename F>
pair<E, F> pair<E, F>::make_pair(E t, F u)
{
  return (pair<E, F>(t, u));
}

#endif // PAIR_HPP
