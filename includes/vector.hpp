#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
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
		: _alloc(alloc), _start(ft_nullptr), _finish(ft_nullptr), _end_of_storage(ft_nullptr) {}	// Default constructor
		explicit vector(size_type n, const value_type& val = value_type(),
										const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _start(ft_nullptr), _finish(ft_nullptr), _end_of_storage(ft_nullptr) {
			_start = _alloc.allocate(n);
			_finish = _start;
			_end_of_storage = _start + n;
			while (n--)
				_alloc.construct(_finish++, val);
		}	// Fill constructor
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _start(ft_nullptr), _finish(ft_nullptr), _end_of_storage(ft_nullptr) {
			// difference_type n = 0;
			// InputIterator tmp = first;
			// while(tmp != last) {
			// 	tmp++;
			// 	n++;
			// }
			difference_type n = last - first;
			_start = _alloc.allocate(n);
			_finish = _start;
			_end_of_storage = _start + n;
			while (n--)
				_alloc.construct(_finish++, *first++);
		}	// Range constructor
		vector(const vector& x)
		: _alloc(x._alloc), _start(ft_nullptr), _finish(ft_nullptr), _end_of_storage(ft_nullptr) {
			difference_type n = x._finish - x._start;
			_start = _alloc.allocate(n);
			_finish = _start;
			_end_of_storage = _start + n;
			pointer tmp = x._start;
			while (n--)
				_alloc.construct(_finish++, *tmp++);
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
		size_type	size() const { return size_type(_finish - _start); }
		size_type	max_size() const { return _alloc.max_size(); }
		void			resize(size_type n, value_type val = value_type()) {
			if (n < size())
				erase(_start + n, _finish);
			else if (n > size())
				insert(_finish, n - size(), val);
		}
		size_type	capacity() const { return size_type(_end_of_storage - _start); }
		bool			empty() const { return _start == _finish;}
		void			reserve(size_type n) {
			if (n > max_size())
				throw std::length_error("Vector reserve error");
			else if (n > capacity()) {
				assign(_start, _finish);
				size_type i = _finish - _start;
				insert(_finish, n - i, value_type());
			}
			// ~vector();
		}
		// Element access:
		reference 			operator[](size_type n) { return *(_start + n); }
		const_reference	operator[](size_type n) const { return *(_start + n); }
		reference				at(size_type n) {
			if (n >= size())
				throw std::out_of_range("Vector at error");
			return (*this)[n];
		}
		const_reference	at(size_type n) {
			if (n >= size())
				throw std::out_of_range("Vector at error");
			return (*this)[n];
		}
		reference				front() { return *_start; }
		const_reference	front() const { return *_start; }
		reference				back() { return *(_finish - 1); }
		const_reference	back() const { return *(_finish - 1); }
		// Modifiers:
		template <class VectorIterator>
		void assign(VectorIterator first, VectorIterator last) {
			clear();
			size_type n = last - first;
			if (n <= capacity()) {
				while (n--)
					_alloc.construct(_finish++, *first++);
			}
			else {
				pointer start = _start;
				pointer end_of_storage = _end_of_storage;
				_start = _alloc.allocate(n);
				_finish = _start;
				_end_of_storage = _start + n;
				while (n--)
					_alloc.construct(_finish++, *first++);
				_alloc.deallocate(start, end_of_storage - start);
			}
		}	// range
		void assign(size_type n, const value_type& val) {
			clear();
			if (n <= capacity()) {
				while (n--)
					_alloc.construct(_finish++, val);
			}
			else {
				pointer start = _start;
				pointer end_of_storage = _end_of_storage;
				_start = _alloc.allocate(n);
				_finish = _start;
				_end_of_storage = _start + n;
				while (n--)
					_alloc.construct(_finish++, val);
				_alloc.deallocate(start, end_of_storage - start);
			}
		}	// fill
		void push_back(const value_type& val) {
			if (_finish == _end_of_storage) {
				if (size() == 0)
					resize(1);
				else
					resize(capacity() * 2);
			}
			_alloc.construct(_finish++, val);
		}
		void pop_back() { _alloc.destroy(--_finish); }
		iterator	insert(iterator position, const value_type& val) {
			insert(position, 1, val);
			return position;
		}	// single element
		void			insert(iterator position, size_type n, const value_type& val) {
			if (size() + n <= capacity()) {
				pointer val_tmp = _finish;
				size_type range = _finish - position;
				_finish += n;
				pointer tmp = _finish;
				while (range--)
					_alloc.construct(--tmp, *(--val_tmp));
				while (n--)
					_alloc.construct(--tmp, val);
			}
			else {
				pointer tmp = _start;
				size_type size = n + size();
				size_type front_part = position - _start;
				size_type back_part = _finish - position - n;
				_start = _alloc.allocate(size);
				_finish = _start;
				_end_of_storage = _start + size;
				while (front_part--) {
					_alloc.construct(_finish++, *tmp);
					_alloc.destroy(tmp++);
				}
				while (n--)
					_alloc.construct(_finish++, val);
				while (back_part--) {
					_alloc.construct(_finish++, *tmp);
					_alloc.destroy(tmp++);
				}
			}
		}	// fill
		template <class VectorIterator>
		void			insert(iterator position, VectorIterator first, VectorIterator last) {
			size_type n = last - first;
			if (size() + n <= capacity()) {
				pointer val_tmp = _finish;
				size_type range = _finish - position;
				_finish += n;
				pointer tmp = _finish;
				while (range--)
					_alloc.construct(--tmp, *(--val_tmp));
				while (n--)
					_alloc.construct(--tmp, *first++);
			}
			else {
				pointer tmp = _start;
				size_type size = n + size();
				size_type front_part = position - _start;
				size_type back_part = _finish - position - n;
				_start = _alloc.allocate(size);
				_finish = _start;
				_end_of_storage = _start + size;
				while (front_part--) {
					_alloc.construct(_finish++, *tmp);
					_alloc.destroy(tmp++);
				}
				while (n--)
					_alloc.construct(_finish++, *first++);
				while (back_part--) {
					_alloc.construct(_finish++, *tmp);
					_alloc.destroy(tmp++);
				}
			}
		}	// range
		iterator erase(iterator position) {
			_alloc.destroy(position);
			size_type n = _finish - position - 1;
			pointer tmp = position;
			while (n--) {
				_alloc.construct(tmp, *(tmp + 1));
				_alloc.destroy(tmp++);
			}
			--_finish;
			return position;
		}
		iterator erase(iterator first, iterator last) {
			pointer tmp = first;
			while (tmp < last)
				_alloc.destroy(tmp++);
			size_type n = _finish - last;
			size_type range = last - first;
			tmp = first;
			while (n--) {
				_alloc.construct(tmp, *last++);
				_alloc.destroy(tmp++);
			}
			_finish -= range;
			return first;
		}	// range
		void swap(vector& x) {
			allocator_type tmp_alloc = x._alloc;
			pointer tmp_start = x._start;
			pointer tmp_finish = x._finish;
			pointer tmp_end_of_storage = x._end_of_storage;

			x._alloc = _alloc;
			x._start = _start;
			x._finish = _finish;
			x._end_of_storage = _end_of_storage;

			_alloc = tmp_alloc;
			_start = tmp_start;
			_finish = tmp_finish;
			_end_of_storage = tmp_end_of_storage;
		}
		void clear() { while (_start < end) _alloc.destroy(_start++); }
		// Allocator:
		allocator_type get_allocator() const { return _alloc; }

		/**
		 * @brief Member variables
		 */
	private:
		allocator_type	_alloc;
		pointer					_start;
		pointer					_finish;
		pointer					_end_of_storage;
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
