#ifndef BITSET_HPP
#define BITSET_HPP
#include <iostream>
#include <stdexcept>
#define nuOfBits (8 * sizeof(unsigned long long))
using ull = unsigned long long;

class bitSet
{
  friend std::ostream& operator<<(std::ostream& os, const bitSet& bset);

public:
  bitSet() noexcept;
  bitSet(size_t countOfBits) noexcept;
  bitSet(const bitSet& object);
  ~bitSet();

public:
  bitSet& set(size_t pos); // set bit true
  bitSet& reset(size_t pos); // set bit false
  bitSet& flip(size_t pos); // toggles the values of bits 
  bool test(size_t pos) const; // accesses specific bit
  // checks if all, any or none of the bits are set to true
  bool all() const noexcept;
  bool any() const noexcept;
  bool none() const noexcept;
  size_t count() const noexcept; // returns the number of bits set to true
  size_t size() const; // returns the number of bits that the bitset holds

public:
  bool operator==(const bitSet& rhs) const noexcept;
  bool operator!=(const bitSet& rhs) const noexcept;
  bitSet& operator=(const bitSet& rhs) noexcept;
  bool operator[](size_t pos) const;
  bitSet& operator&=(const bitSet& other);
  bitSet& operator|=(const bitSet& other);
  bitSet& operator^=(const bitSet& other);
  bitSet operator~() const noexcept;

private:
  size_t helper(size_t countOfBits) const;
  void ullToBinDigit(ull in, int* out) const;
  size_t countSetBits(ull num) const;

private:
  ull* m_buff;
  size_t m_size;
};

void bitSet::ullToBinDigit(ull in, int* out) const
{
  ull mask = 1;
  mask = mask << (nuOfBits - 1);
  for (int i = 0; i < nuOfBits; ++i) {
    out[i] = (in & mask) ? 1 : 0;
    in <<= 1;
  }
}

std::ostream& operator<<(std::ostream& os, const bitSet& bset)
{
  for (int i = 0; i < bset.m_size; ++i) {
    int digit[nuOfBits];
    bset.ullToBinDigit(bset.m_buff[i], digit);
    for (int i = 0; i < nuOfBits; ++i) {
      os << digit[i]; 
    }
    os << " ";
  }
  return os;
}

bool bitSet::operator==(const bitSet& rhs) const noexcept {
  if (this->m_size != rhs.m_size) {
    return false;
  }
  for (int i = 0; i < this->m_size; ++i) {
    if (this->m_buff[i] != rhs.m_buff[i]) {
      return false;
    }
  }
  return true;
}

bool bitSet::operator!=(const bitSet& rhs) const noexcept {
  return !(*this == rhs);
}

bitSet& bitSet::operator=(const bitSet& rhs) noexcept {
  if (*this == rhs) {
    return *this;
  }
  delete[] m_buff;
  this->m_size = rhs.m_size;
  this->m_buff = new ull[this->m_size];
  for (int i = 0; i < this->m_size; ++i) {
    this->m_buff[i] = rhs.m_buff[i];
  }
  return *this;
}

bitSet bitSet::operator~() const noexcept {
  bitSet res(this->m_size * nuOfBits);
  for (int i = 0; i < this->m_size; ++i) {
    res.m_buff[i] = ~this->m_buff[i];
  }
  return res;
}

bool bitSet::operator[](size_t pos) const {
  if (pos >= (nuOfBits * m_size)) {
    throw std::out_of_range("Error! : Index is out of range");
  }
  ull mask = 1;
  if (m_buff[m_size - (pos / nuOfBits) - 1] & (mask << (pos % nuOfBits))) {
    return 1;
  }
  return 0;
}

bitSet& bitSet::operator|=(const bitSet& other) {
  if (other.m_size != this->m_size) {
    throw std::invalid_argument("Error! : Size mismatch");
  }
  for (int i = 0; i < this->m_size; ++i) {
    this->m_buff[i] |= other.m_buff[i];
  }
  return *this;
}

bitSet& bitSet::operator&=(const bitSet& other) {
  if (other.m_size != this->m_size) {
    throw std::invalid_argument("Error! : Size mismatch");
  }
  for (int i = 0; i < this->m_size; ++i) {
    this->m_buff[i] &= other.m_buff[i];
  }
  return *this;
}

bitSet& bitSet::operator^=(const bitSet& other) {
  if (other.m_size != this->m_size) {
    throw std::invalid_argument("Error! : Size mismatch");
  }
  for (int i = 0; i < this->m_size; ++i) {
    this->m_buff[i] ^= other.m_buff[i];
  }
  return *this;
}

size_t bitSet::helper(size_t countOfBits) const {
  size_t res = 0; 
  if (countOfBits <= nuOfBits) {
    res = 1;
    return res;
  }
  res = countOfBits / nuOfBits;
  if (countOfBits % nuOfBits) {
    res++;
  }
  return res;
}

bitSet::bitSet() noexcept
  : m_buff(nullptr)
  , m_size(0)
{ }

bitSet::bitSet(size_t countOfBits) noexcept {
  m_size = this->helper(countOfBits);
  m_buff = new ull[m_size];
  for (int i = 0; i < m_size; ++i) {
    m_buff[i] = 0;
  }
}

bitSet::bitSet(const bitSet& object) {
  this->m_size = object.m_size;
  this->m_buff = new ull[this->m_size];
  for (int i = 0; i < this->m_size; ++i) {
    this->m_buff[i] = object.m_buff[i];
  }
}

bitSet::~bitSet() {
  delete[] m_buff;
  m_buff = nullptr;
}

bitSet& bitSet::set(size_t pos) {
  if (pos >= (nuOfBits * m_size)) {
    throw std::out_of_range("Error! : Index is out of range");
  }
  ull mask = 1;
  m_buff[m_size - (pos / nuOfBits) - 1] |= (mask << (pos % nuOfBits));
  return *this;
}

bitSet& bitSet::reset(size_t pos) {
  if (pos >= (nuOfBits * m_size)) {
    throw std::out_of_range("Error! : Index is out of range");
  }
  ull mask = 1;
  m_buff[m_size - (pos / nuOfBits) - 1] &= ~(mask << (pos % nuOfBits));
  return *this;
}

bitSet& bitSet::flip(size_t pos) {
  if (pos >= (nuOfBits * m_size)) {
    throw std::out_of_range("Error! : Index is out of range");
  }
  ull mask = 1;
  m_buff[m_size - (pos / nuOfBits) - 1] ^= (mask << (pos % nuOfBits));
  return *this;
}

bool bitSet::test(size_t pos) const {
  if (pos >= (nuOfBits * m_size)) {
    throw std::out_of_range("Error! : Index is out of range");
  }
  ull mask = 1;
  return (m_buff[m_size - (pos / nuOfBits) - 1] & (mask << (pos % nuOfBits))) != 0;
}

size_t bitSet::size() const {
  return (this->m_size * nuOfBits);
}

bool bitSet::any() const noexcept { 
  for (int i = 0; i < m_size; ++i) {
    if (m_buff) {
      return true;
    }
  }
  return false;
}

bool bitSet::none() const noexcept {
  return !this->any();
}

bool bitSet::all() const noexcept {
  ull mask = 0;
  mask = ~mask;
  for (int i = 0; i < m_size; ++i) {
    if ((m_buff[i] & mask) != mask) {
      return false;
    }
  }
  return true;
}

size_t bitSet::countSetBits(ull num) const {
  size_t res = 0;
  while (num) {
    res += num & 1;
    num >>= 1;
  }
  return res;
}

size_t bitSet::count() const noexcept {
  size_t res = 0;
  for (int i = 0; i < m_size; ++i) {
    res += countSetBits(m_buff[i]);
  }
  return res;
}

#endif // BITSET_HPP
