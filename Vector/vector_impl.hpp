#ifndef VECTOR_IMPL_HPP
#define VECTOR_IMPL_HPP

#ifndef VECTOR_HPP
#error [Error] vector_impl.hpp should only be included from vector.hpp.
#endif

#include <iostream>
#include <algorithm>
#include <limits>
#include <memory>

namespace vstd {
	
	// Start of Iterator implementation
	template < typename T >
	random_access_iterator<T>::random_access_iterator()
		: m_ptr(nullptr)
	{ }

	template < typename T >
	random_access_iterator<T>::random_access_iterator(
			                       random_access_iterator<T>::pointer ptr) 
		: m_ptr(ptr)
	{ }

	template < typename T >
	random_access_iterator<T>::random_access_iterator(
			                       const random_access_iterator<T>& other)
		: m_ptr(other.m_ptr)
	{ }
	
	template < typename T > 
	random_access_iterator<T>::~random_access_iterator() { 
		//empty  
	}

	template < typename T >
	random_access_iterator<T>::operator 
	random_access_iterator<const T>() const {
		return random_access_iterator<const T>(m_ptr);
	}

	template < typename T >
	random_access_iterator<T>& random_access_iterator<T>::operator=(
			                       const random_access_iterator& other) {
		if (&other != this) { 
			this->m_ptr = other->m_ptr;
		}
		return *this;
	}	

	template < typename T >
	typename random_access_iterator<T>::reference 
	random_access_iterator<T>::operator*() const {
		return *m_ptr;
  }

	template < typename T >
  typename random_access_iterator<T>::pointer 
	random_access_iterator<T>::operator->() {
		return m_ptr;
  }
  
	template < typename T >
	random_access_iterator<T>& random_access_iterator<T>::operator++() { 
		++m_ptr;
    return *this;
  }

	template < typename T >
	random_access_iterator<T> random_access_iterator<T>::operator++(int) {
		random_access_iterator<T> tmp = *this;
    ++(*this);
    return tmp;
	}

	template < typename T >
	random_access_iterator<T>& random_access_iterator<T>::operator--() { 
		--m_ptr;
    return *this;
  }

	template < typename T >
  random_access_iterator<T> random_access_iterator<T>::operator--(int) {
		random_access_iterator<T> tmp = *this;
    --(*this);
    return tmp;
	}

	template < typename T >
  bool operator==(const random_access_iterator<T>& a, 
			            const random_access_iterator<T>& b) {
		return a.m_ptr == b.m_ptr;
  };

	template < typename T >
  bool operator!=(const random_access_iterator<T>& a, 
			            const random_access_iterator<T>& b) { 
		return a.m_ptr != b.m_ptr; 
	};

	template < typename  T >
	typename random_access_iterator<T>::reference 
	random_access_iterator<T>::operator[](
			        typename random_access_iterator<T>::difference_type num) const {
		return *(m_ptr + num);
	}

	template < typename T > 
  random_access_iterator<T> random_access_iterator<T>::operator+(
			        typename random_access_iterator<T>::difference_type num) const {
		return random_access_iterator<T>(m_ptr + num);
	}

	template < typename T >
	random_access_iterator<T> random_access_iterator<T>::operator-(
			        typename random_access_iterator<T>::difference_type num) const {
		return random_access_iterator<T>(m_ptr - num);
	}

	template < typename T >
	random_access_iterator<T>& random_access_iterator<T>::operator+=(
		 	        typename random_access_iterator<T>::difference_type num) {
		m_ptr += num;
		return *this;
	}

	template < typename T >
	random_access_iterator<T>& random_access_iterator<T>::operator-=(
			        typename random_access_iterator<T>::difference_type num) {
		m_ptr -= num;
		return *this;
	}

	template < typename T >
	typename random_access_iterator<T>::difference_type 
	random_access_iterator<T>::operator-(
			                       const random_access_iterator<T>& other) const {
		return m_ptr - other.m_ptr;
	}

	template < typename T > 
	bool random_access_iterator<T>::operator>(
			                       const random_access_iterator<T>& other) const {
		return m_ptr > other.m_ptr;
	}

	template < typename T > 
	bool random_access_iterator<T>::operator<(
			                       const random_access_iterator<T>& other) const {
		return m_ptr < other.m_ptr;
	}

	template < typename T > 
	bool random_access_iterator<T>::operator>=(
			                       const random_access_iterator<T>& other) const {
		return m_ptr >= other.m_ptr;
	}

	template < typename T > 
	bool random_access_iterator<T>::operator<=(
			                       const random_access_iterator<T>& other) const {
		return m_ptr <= other.m_ptr;
	}
	// End of Iterator implementation

	// Start of Vector implementation
	template < typename T, typename Allocator >
	constexpr vector<T, Allocator>::vector(const Allocator& alloc) noexcept 
		: m_alloc(alloc)
		, m_data(nullptr)
    , m_size(0)
    , m_capacity(0)
	{ }

	template < typename E, typename Alloc >
	std::ostream& operator>>(std::ostream& os, const vector<E, Alloc>& vec) {
		for (const auto& element : vec) {
			os << element << ' ';
		}
		return os;
	}

	template < typename E, typename Alloc >
	std::istream& operator<<(std::istream& in, vector<E, Alloc>& vec) {
		for (auto& element : vec) {
			in >> element;
		}
		return in;
	}

	template < typename T, typename Alloc > 
	constexpr vector<T, Alloc>::vector(typename vector<T, Alloc>::size_type count, 
			                               const T& value, const Alloc& alloc) 
		: m_alloc(alloc) 
	{
		m_size = count;
    m_capacity = count;
    m_data = m_alloc.allocate(m_capacity);
    for (size_type i = 0; i < m_size; ++i) {
			m_alloc.construct(m_data + i, value);
    }
	}

	template < typename T, typename Alloc >
	constexpr vector<T, Alloc>::vector(typename vector<T, Alloc>::size_type count, 
			                               const Alloc& alloc) 
		: m_alloc(alloc)
	{
		m_size = count;
		m_capacity = count;
		m_data = m_alloc.allocate(m_capacity);
		for (size_type i = 0; i < m_size; ++i) {
			m_alloc.construct(m_data + i);
		}
	}

	template < typename T, typename Alloc >
	constexpr vector<T, Alloc>::vector(const vector<T, Alloc>& other) 
		: m_size(other.m_size)
		, m_capacity(other.m_capasity)
		, m_alloc(other.m_alloc)
	{
		if (&other != this) {
			m_data = m_alloc.allocate(m_capacity);
			for (size_type i = 0; i < m_size; ++i) {
				m_alloc.construct(m_data + i, other.m_data[i]);
			}
		}
	}

	template < typename T, typename Alloc > 
	constexpr vector<T, Alloc>::vector(const vector<T, Alloc>& other, 
			                               const Alloc& alloc) 
		: m_size(other.m_size)
		, m_capacity(other.m_capasity)
		, m_alloc(alloc)
	{
		if (&other != this) {
			m_data = m_alloc.allocate(m_capacity);
			for (size_type i = 0; i < m_size; ++i) { 
				m_alloc.construct(m_data + i, other.m_data[i]);
			}
		}
	}

	template < typename T, typename Alloc >
	constexpr vector<T, Alloc>::vector(vector&& other) noexcept
		: m_data(other.m_data)
		, m_size(other.m_size)
		, m_capacity(other.m_capacity)
		, m_alloc(std::move(other.m_alloc)) 
	{
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
	}

	template < typename T, typename Alloc >
	constexpr vector<T, Alloc>::vector(vector<T, Alloc>&& other, 
			                               const Alloc& alloc) 
		: m_data(other.m_data)
		, m_size(other.m_size)
		, m_capacity(other.m_capacity)
		, m_alloc(std::move(alloc)) 
	{ 
		other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
	}

	template<typename T, typename Alloc>
	constexpr vector<T, Alloc>::vector(std::initializer_list<T> init, 
			                               const Alloc& alloc)
		: m_size(init.size())
		, m_capacity(init.size())
		, m_alloc(alloc) 
	{
		m_data = m_alloc.allocate(m_capacity);
    std::uninitialized_copy(init.begin(), init.end(), m_data);
	}

	template <typename T, typename Alloc>
	constexpr void vector<T, Alloc>::clear() noexcept {
		for (size_type i = 0; i < m_size; ++i) {
			m_alloc.destroy(m_data + i);
    }
  	m_alloc.deallocate(m_data, m_capacity);
 	 	m_data = nullptr;
  	m_size = 0;
  	m_capacity = 0;
	}

	template < typename T, typename Alloc >
	vector<T, Alloc>::~vector() {
	  clear();
	}

	template < typename T, typename Alloc >
	constexpr vector<T, Alloc>& 
	vector<T, Alloc>::operator=(const vector& other) {
		if (&other != this) {
			clear();
			m_alloc.deallocate(m_data, m_capacity);

			m_capacity = other.m_capacity;
			m_size = other.size;
			m_data = m_alloc.allocate(m_capacity);
			for (size_type i = 0; i < m_size; ++i) {
				m_alloc.construct(m_data + i, other.m_data[i]);
			}
		}
		return *this;
	}

	template < typename T, typename Alloc >
	constexpr vector<T, Alloc>& 
	vector<T, Alloc>::operator=(vector&& other) noexcept {
		if (&other != this) {
			clear();
			m_data = other.m_data;
			m_size = other.m_size;
			m_capacity = other.m_capacity;
	  	m_alloc = std::move(other.m_alloc);

			other.m_data = nullptr; 
			other.m_size = 0;
			other.m_capacity = 0;
		}
		return *this;
	}

	template < typename T, typename Alloc >
	constexpr vector<T, Alloc>& 
	vector<T, Alloc>::operator=(std::initializer_list<T> ilist) {
		clear();
    reserve(ilist.size());
    for (const auto& element : ilist) {
			push_back(element);
		}
		return *this;
	}

	template < typename T, typename Alloc >
	constexpr bool vector<T, Alloc>::empty() const noexcept {
		return m_size == 0 ? true : false;
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::size_type 
	vector<T, Alloc>::size() const noexcept {
		return m_size;
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::size_type 
	vector<T, Alloc>::max_size() const noexcept {
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	template < typename T, typename Alloc >
  constexpr void vector<T, Alloc>::reserve(typename vector<T, Alloc>::size_type new_cap) {
		if (new_cap > m_capacity) {
			T* new_data = m_alloc.allocate(new_cap);
    	for (size_type i = 0; i < m_size; ++i) {
				m_alloc.construct(new_data + i, std::move_if_noexcept(m_data[i]));
      	m_alloc.destroy(m_data + i);
    	}
			m_alloc.deallocate(m_data, m_capacity);
    	m_data = new_data;
    	m_capacity = new_cap;
		}
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::size_type 
	vector<T, Alloc>::capacity() const noexcept {
		return m_capacity;
	}

	template < typename T, typename Alloc >
	constexpr void vector<T, Alloc>::shrink_to_fit() {
		m_capacity = m_size;
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::reference 
	vector<T, Alloc>::operator[](typename vector<T, Alloc>::size_type pos) {
		return *(m_data + pos);
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_reference 
	vector<T, Alloc>::operator[](size_type pos) const {
		return m_data[pos]; 
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::reference 
	vector<T, Alloc>::front() { 
		return m_data[0];
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_reference 
	vector<T, Alloc>::front() const {
		return m_data[0];
	}

	template <typename T, typename Alloc>
	constexpr typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
    return m_data[m_size - 1];
	}

	template <typename T, typename Alloc>
	constexpr typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
    return m_data[m_size - 1];
	}

	template< typename E, typename Alloc = std::allocator<E> >
  constexpr bool operator==(const vector<E, Alloc>& lhs, 
			                      const vector<E, Alloc>& rhs) {
		if (lhs.m_size != rhs.m_size) {
			return false;
		}
		for (int i = 0; i < lhs.m_size; ++i) {
			if (lhs.m_data[i] != rhs.m_data[i]) {
				return false;
			}
		}
		return true;
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_iterator 
	vector<T, Alloc>::begin() const noexcept {
		return const_iterator(m_data);
	}

	template< typename T, typename Alloc>
	constexpr typename vector<T, Alloc>::pointer 
	vector<T, Alloc>::data() noexcept {
    return m_data;
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::iterator 
	vector<T, Alloc>::begin() noexcept {
		return iterator(m_data);
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_iterator 
	vector<T, Alloc>::cbegin() const noexcept {
		return const_iterator(m_data);
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::iterator 
	vector<T, Alloc>::end() noexcept {
		return iterator(m_data + m_size);
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_iterator 
	vector<T, Alloc>::end() const noexcept {
		return const_iterator(m_data + m_size);
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_iterator 
	vector<T, Alloc>::cend() const noexcept {
		return const_iterator(m_data + m_size);
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::reverse_iterator 
	vector<T, Alloc>::rbegin() noexcept {
		return reverse_iterator(end());
	}

	template < typename T, typename Alloc > 
	constexpr typename vector<T, Alloc>::const_reverse_iterator 
	vector<T, Alloc>::rbegin() const noexcept {
		return const_reverse_iterator(end());
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_reverse_iterator
	vector<T, Alloc>::crbegin() const noexcept {
		return const_reverse_iterator(cbegin());
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() noexcept {
    return reverse_iterator(m_data);
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_reverse_iterator 
	vector<T, Alloc>::rend() const noexcept {
		return const_reverse_iterator(m_data);
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_reverse_iterator 
	vector<T, Alloc>::crend() const noexcept {
		return const_reverse_iterator(m_data);
	}

	template < typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator!=(const vector<E, Alloc>& lhs, 
			                      const vector<E, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template < typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator<(const vector<E, Alloc>& lhs, 
			                     const vector<E, Alloc>& rhs) {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());		 
	}

	template < typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator<=(const vector<E, Alloc>& lhs, 
			                      const vector<E, Alloc>& rhs) {
		return lhs < rhs || lhs == rhs;
	}

	template < typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator>(const vector<E, Alloc>& lhs, 
			                     const vector<E, Alloc>& rhs) {
		return lhs != rhs && !(lhs < rhs);
	}

	template < typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator>=(const vector<E, Alloc>& lhs, 
			                      const vector<E, Alloc>& rhs) {
		return lhs == rhs || lhs > rhs;
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::reference 
	vector<T, Alloc>::at(size_type pos) {
    if (pos >= m_size) {
        throw std::out_of_range("Invalid index");
    }
    return m_data[pos];
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::const_reference 
	vector<T, Alloc>::at(size_type pos) const {
    if (pos >= m_size) {
        throw std::out_of_range("Invalid index");
    }
    return m_data[pos];
	}

	template < typename T, typename Alloc >
	constexpr void vector<T, Alloc>::push_back(const T& value) {
		if (m_size >= m_capacity) {
			reserve(m_capacity > 0 ? 2 * m_capacity : 1);
		}
		m_alloc.construct(m_data + m_size, value);
		++m_size;
	}

	template < typename T, typename Alloc > 
	constexpr void vector<T, Alloc>::push_back(T&& value) {
		if (m_size >= m_capacity) {
			reserve(m_capacity > 0 ? 2 * m_capacity : 1);
		}
		m_alloc.construct(m_data + m_size, value);
		++m_size;
	}

	template < typename T, typename Alloc >
	constexpr void vector<T, Alloc>::swap(vector& other) noexcept {
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_alloc, other.m_alloc);
	}

	template < typename T, typename Alloc >
	constexpr void vector<T, Alloc>::pop_back() {
		m_alloc.destroy(m_data + m_size - 1);
		m_size--;
	}

	template <typename T, typename Alloc>
	constexpr typename vector<T, Alloc>::iterator
	vector<T, Alloc>::insert(typename vector<T, Alloc>::const_iterator pos,
                           const T& value) {
		const size_type insertionIndex = pos - cbegin();
		if (m_size >= m_capacity) {
    	reserve((m_capacity > 0) ? 2 * m_capacity : 1);
		}

  	iterator insertPosition = begin() + insertionIndex;
  	for (iterator it = end(); it != insertPosition; --it) {
    	m_alloc.construct(&(*it), std::move(*(it - 1)));
  	}

 	 	m_alloc.construct(&(*insertPosition), value);
 		++m_size;
  	return insertPosition;
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::iterator 
	vector<T, Alloc>::insert(typename vector<T, Alloc>::const_iterator pos, 
			                     T&& value) {
		const size_type insertionIndex = pos - cbegin();

  	if (m_size >= m_capacity) {
    	reserve((m_capacity > 0) ? 2 * m_capacity : 1);
  	}

  	iterator insertPosition = begin() + insertionIndex;
  	for (iterator it = end(); it != insertPosition; --it) {
    	m_alloc.construct(&(*it), std::move(*(it - 1)));
  	}

  	m_alloc.construct(&(*insertPosition), std::move(value));
  	++m_size;
  	return insertPosition;
	}

	template < typename T, typename Alloc >
	constexpr typename vector<T, Alloc>::iterator 
	vector<T, Alloc>::erase(typename vector<T, Alloc>::const_iterator first, 
													typename vector<T, Alloc>::const_iterator last) {
		if (first < cbegin() || last > cend() || first > last) {
			throw std::out_of_range("Invalid iterator");
		}

  	const size_type eraseCount = last - first;
 	 	iterator dest = begin() + (first - cbegin());
 		iterator src = dest + eraseCount;
  	for (size_type i = 0; i < (m_size - eraseCount); ++i) {
			*dest = std::move(*src);
    	++dest;
    	++src;
  	}

  	for (iterator it = end() - eraseCount; it != end(); ++it) {
    	m_alloc.destroy(&it);
  	}
  	m_size -= eraseCount;
  	return begin() + (first - cbegin());
	}

	template < typename T, typename Alloc >
	constexpr void vector<T, Alloc>::resize(typename vector<T, Alloc>::size_type count) {
		if (count > m_size) {
      if (count > m_capacity) {
        reserve((m_capacity > 0) ? 2 * m_capacity : 1);
      }
    }
    else if (count < m_size) {
      for (size_type i = count; i < m_size; ++i) {
        m_alloc.destroy(m_data + i);
      }
    }
  	m_size = count;
	}

	template < typename T, typename Alloc >
	constexpr void vector<T, Alloc>::resize(typename vector<T, Alloc>::size_type count, 
			                  const typename vector<T, Alloc>::value_type& value) {
		if (count > m_size) {
			if (count > m_capacity) {
				reserve((m_capacity > 0) ? 2 * m_capacity : 1);
			}
			for (size_type i = m_size; i < count; ++i) {
				m_alloc.construct(m_data + i, value);
			}
		} 
		else if (count < m_size) {
			for (size_type i = count; i < m_size; ++i) {
				m_alloc.destroy(m_data + i);
			}
		}
		m_size = count;
	}

	// End of Vector implementation

} // namespace vstd

#endif // VECTOR_IMPL_HPP
