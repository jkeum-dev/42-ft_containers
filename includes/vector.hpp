#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "VectorIterator.hpp"

namespace ft
{
	/**
	 * @brief vector class
	 * 
	 * @tparam T 
	 * @tparam Alloc 
	 */
	template < class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		/**
		 * @brief Member types
		 * https://www.cplusplus.com/reference/vector/vector/
		 */
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
		 * @brief Member functions
		 * https://www.cplusplus.com/reference/vector/vector/
		 */
		explicit vector(const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _start(ft_nullptr), _finish(ft_nullptr) {}	// Default constructor
		explicit vector(size_type n, const value_type& val = value_type(),
										const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _start(ft_nullptr), _finish(ft_nullptr) {
			_start = _alloc.allocate(n);
			_finish = _start;
			while (n--) {
				_alloc.construct(_finish, val);
				_finish++;
			}
		}	// Fill constructor
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _start(ft_nullptr), _finish(ft_nullptr) {
			// difference_type n = 0;
			// InputIterator tmp = first;
			// while(tmp != last) {
			// 	tmp++;
			// 	n++;
			// }
			difference_type n = last - first;
			_start = _alloc.allocate(n);
			_finish = _start;
			while (n--) {
				_alloc.construct(_finish, *first);
				_finish++;
				first++;
			}
		}	// Range constructor
		vector(const vector& x)
		: _alloc(x._alloc), _start(ft_nullptr), _finish(ft_nullptr) {
			difference_type n = x._finish - x._start;
			_start = _alloc.allocate(n);
			_finish = _start;
			pointer tmp = x._start;
			while (n--) {
				_alloc.construct(_finish, *tmp);
				_finish++;
				tmp++;
			}
		}	// Copy constructor
		~vector() {
			clear();
			_alloc.deallocate(_start, _finish - _start);
		}	// Destructor
		vector& operator=(const vector& x) {
			if (this != &x) {
				this->clear();
				this->assign(x.begin(), x.end());
			}
			return *this;
		}	// Assignment operator
		// Iterators:
		iterator 				begin() { return _start; }
		const_iterator	begin() const { return _start; }
		iterator				end() { return _finish; }
		const_iterator	end() const { return _finish; }
		reverse_iterator				rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator				rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }
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

		/**
		 * @brief Member variables
		 */
	private:
		allocator_type	_alloc;
		pointer					_start;
		pointer					_finish;
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
