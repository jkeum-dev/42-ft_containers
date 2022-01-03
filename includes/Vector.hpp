#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "VectorIterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		/**
		 * Member types
		**/
		typedef T																					value_type;
		typedef Alloc																			allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::VectorIterator<value_type>						iterator;
		typedef ft::VectorIterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type				size_type;

		/**
		 * Member functions
		**/
		explicit vector(const allocator_type& alloc = allocator_type());	// Default constructor
		explicit vector(size_type n, const value_type& val = value_type(),
										const allocator_type& alloc = allocator_type());	// Fill constructor
		template <class VectorIterator>
		vector(VectorIterator first, VectorIterator last,
					const allocator_type& alloc = allocator_type());	// Range constructor
		vector(const vector& x);	// Copy constructor
		~vector();	// Destructor
		vector& operator=(const vector& x);	// Assignment operator
		// Iterators:
		iterator 				begin();
		const_iterator	begin() const;
		iterator				end();
		const_iterator	end() const;
		reverse_iterator				rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator				rend();
		const_reverse_iterator	rend() const;
		// Capacity:
		size_type	size() const;
		size_type	max_size() const;
		void			resize(size_type n, value_type val = value_type());
		size_type	capacity() const;
		bool			empty() const;
		void			reserve(size_type n);
		// Element access:
		reference 			operator[](size_type n);
		const_reference	operator[](size_type n) const;
		reference				at(size_type n);
		const_reference	at(size_type n);
		reference				front();
		const_reference	front() const;
		reference				back();
		const_reference	back() const;
		// Modifiers:
		template <class VectorIterator>
		void assign(VectorIterator first, VectorIterator last);	// range
		void assign(size_type n, const value_type& val);	// fill
		void push_back(const value_type& val);
		void pop_back();
		iterator	insert(iterator position, const value_type& val);	// single element
		void			insert(iterator position, size_type n, const value_type& val);	// fill
		template <class VectorIterator>
		void			insert(iterator position, VectorIterator first, VectorIterator last);	// range
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);	// range
		void swap(vector& x);
		void clear();
		// Allocator:
		allocator_type get_allocator() const;
	};

	// Relational operators
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	// swap
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y);
} // namespace ft

#endif
