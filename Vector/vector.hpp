/*
 * Project:     Vector
 * Author:      Areg Oseyan
 *
 * Description: This file contain the declaration of the vector class template. 
 *              It include the necessary headers and define the class structure, 
 *              member functions, and member variables of the vector. 
 *              The vector class typically have functions for element access, 
 *              modification, insertion, deletion, and other operations. 
 *              Also defined iterator struct, type of` random_access_iterator.
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

// Include necessary headers
#include <memory>
#include <iostream>

namespace vstd {

// Start of Iterator declaration
	template < typename T >
	struct random_access_iterator {
	public:
		using random_access_iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

	public:
		random_access_iterator();
		random_access_iterator(pointer ptr);
		random_access_iterator(const random_access_iterator& other);
		random_access_iterator& operator=(const random_access_iterator& other);
		operator random_access_iterator<const T>() const;
		virtual ~random_access_iterator();

	public:
		reference operator*() const;
		pointer operator->();
		random_access_iterator& operator++();
		random_access_iterator operator++(int);
		random_access_iterator& operator--();
		random_access_iterator operator--(int);
		reference operator[](difference_type num) const;
		random_access_iterator operator+(difference_type num) const;
		random_access_iterator operator-(difference_type num) const;
		random_access_iterator& operator+=(difference_type num);
		random_access_iterator& operator-=(difference_type num);
		difference_type operator-(const random_access_iterator& other) const;
		bool operator>(const random_access_iterator& other) const;
		bool operator<(const random_access_iterator& other) const;
		bool operator>=(const random_access_iterator& other) const;
		bool operator<=(const random_access_iterator& other) const;

	public:
		template < typename E >
    friend bool operator==(const random_access_iterator<E>& a, 
				                   const random_access_iterator<E>& b);
		template < typename F >
		friend bool operator!=(const random_access_iterator<F>& a, 
				                   const random_access_iterator<F>& b);

	private:
		pointer m_ptr;
	};
// End of Iterator declaration

// Start of Vector declaration
	template < typename T, typename Allocator = std::allocator<T> >
	class vector {
		// Non-member functions
		template< typename E, typename Alloc >
		friend std::ostream& operator>>(std::ostream& os, const vector<E, Alloc>& vec);
		template< typename E, typename Alloc >
		friend std::istream& operator<<(std::istream& in, vector<E, Alloc>& vec); 

	public:
		// Member types
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename std::allocator_traits<Allocator>::pointer pointer;
		typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;
		typedef random_access_iterator<T> iterator;
		typedef random_access_iterator<const T> const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		// Member functions
	public:
		constexpr explicit vector(const Allocator& alloc = Allocator()) noexcept;
		constexpr vector(size_type count, const T& value, 
				                              const Allocator& alloc = Allocator());
		constexpr explicit vector(size_type count, 
				                      const Allocator& alloc = Allocator());
		constexpr vector(const vector& other);
		constexpr vector(const vector& other, const Allocator& alloc = Allocator());
		constexpr vector(vector&& other) noexcept;
		constexpr vector(vector&& other, const Allocator& alloc = Allocator());
		constexpr vector(std::initializer_list<T> init, 
				             const Allocator& alloc = Allocator());
		virtual ~vector();

		constexpr vector& operator=(const vector& other);
		constexpr vector& operator=(vector&& other) noexcept;
		constexpr vector& operator=(std::initializer_list<T> ilist);

		// Element access
	public:
		constexpr reference at(size_type pos);
		constexpr const_reference at(size_type pos) const;
		constexpr reference operator[](size_type pos);
		constexpr const_reference operator[](size_type pos) const;
		constexpr reference front();
		constexpr const_reference front() const;
		constexpr reference back();
		constexpr const_reference back() const;

		// iterators
	public:
		constexpr iterator begin() noexcept;
		constexpr const_iterator begin() const noexcept;
		constexpr const_iterator cbegin() const noexcept;
		constexpr iterator end() noexcept; 
		constexpr const_iterator end() const noexcept;
		constexpr const_iterator cend() const noexcept; 
		constexpr reverse_iterator rbegin() noexcept;
		constexpr const_reverse_iterator rbegin() const noexcept;
		constexpr const_reverse_iterator crbegin() const noexcept;
		constexpr reverse_iterator rend() noexcept;
		constexpr const_reverse_iterator rend() const noexcept;
		constexpr const_reverse_iterator crend() const noexcept;

		// Capacity
	public:
		constexpr bool empty() const noexcept;
		constexpr size_type size() const noexcept;
		constexpr size_type max_size() const noexcept;
		constexpr void reserve(size_type new_cap);
		constexpr size_type capacity() const noexcept;
		constexpr void shrink_to_fit();
		constexpr pointer data() noexcept;

		// Modifiers
	public:
		constexpr void clear() noexcept;
		constexpr iterator insert(const_iterator pos, const T& value);
		constexpr iterator insert(const_iterator pos, T&& value);
		constexpr iterator erase(const_iterator first, const_iterator last);
		constexpr void push_back(const T& value);
		constexpr void push_back(T&& value);
		constexpr void pop_back();
		constexpr void resize(size_type count);
		constexpr void resize(size_type count, const value_type& value);
		constexpr void swap(vector& other) noexcept;

	private:
		T* m_data;
		size_type m_size;
		size_type m_capacity;
		allocator_type m_alloc;
	};

	// Non-member functions
	template< typename E, typename Alloc = std::allocator<E> >
  constexpr bool operator==(const vector<E, Alloc>& lhs, 
			                      const vector<E, Alloc>& rhs);
	template< typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator!=(const vector<E, Alloc>& lhs, 
			                      const vector<E, Alloc>& rhs);
	template< typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator<(const vector<E, Alloc>& lhs, 
			                     const vector<E, Alloc>& rhs);
	template< typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator<=(const vector<E, Alloc>& lhs, 
			                      const vector<E, Alloc>& rhs);
	template< typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator>(const vector<E, Alloc>& lhs, 
			                     const vector<E, Alloc>& rhs);
	template< typename E, typename Alloc = std::allocator<E> >
	constexpr bool operator>=(const vector<E, Alloc>& lhs, 
			                      const vector<E, Alloc>& rhs);
// End of Vector declaration

} // namespace vstd

// Include the implementation file
#include "vector_impl.hpp"

#endif // VECTOR_HPP
