#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP

#include "Iterators.hpp"
#include "utils.hpp"

namespace ft
{
	template <typename T>
	class VectorIterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
	public :
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type				value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer						pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference					reference;

		VectorIterator(pointer ptr = ft_nullptr) : _ptr(ptr) {}					// Default constructor
		VectorIterator(const VectorIterator& copy) : _ptr(copy._ptr) {}	// Copy constructor
		VectorIterator& operator=(const VectorIterator& copy) { if (this != copy) this->_ptr = copy._ptr; return *this; }	// Assignment operator
		virtual ~VectorIterator() {}	// Destructor
		pointer const & getPtr() const { return _ptr; }	// getter
		/**
		 * operators
		**/
		reference operator*() const { return *_ptr;}
		pointer operator->() const { return _ptr; }
		VectorIterator& operator++() { ++_ptr; return *this; }
		VectorIterator operator++(int) { VectorIterator tmp = *this; ++_ptr; return tmp; }
		VectorIterator& operator--() { --_ptr; return *this; }
		VectorIterator operator--(int) { VectorIterator tmp = *this; --_ptr; return tmp; }
		VectorIterator operator+(difference_type n) const { return _ptr + n; }	// iter + n
		VectorIterator operator-(difference_type n) const { return _ptr - n; }	// iter - n
		VectorIterator& operator+=(difference_type n) { _ptr += n; return *this; }
		VectorIterator& operator-=(difference_type n) { _ptr -= n; return *this; }
		reference operator[](difference_type n) const { return *(_ptr + n); }

	private :
		pointer _ptr;
	};

	/**
	 * operators
	**/
	template <typename T>
	bool operator==(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T> rIter) { return lIter.getPtr() == rIter.getPtr(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator==(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T_c> rIter) { return lIter.getPtr() == rIter.getPtr(); }
	
	template <typename T>
	bool operator!=(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T> rIter) { return lIter.getPtr() != rIter.getPtr(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator!=(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T_c> rIter) { return lIter.getPtr() != rIter.getPtr(); }
	
	template <typename T>
	bool operator<(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T> rIter) { return lIter.getPtr() < rIter.getPtr(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator<(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T_c> rIter) { return lIter.getPtr() < rIter.getPtr(); }
	
	template <typename T>
	bool operator>(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T> rIter) { return lIter.getPtr() > rIter.getPtr(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator>(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T_c> rIter) { return lIter.getPtr() > rIter.getPtr(); }
	
	template <typename T>
	bool operator<=(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T> rIter) { return lIter.getPtr() <= rIter.getPtr(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator<=(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T_c> rIter) { return lIter.getPtr() <= rIter.getPtr(); }
	
	template <typename T>
	bool operator>=(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T> rIter) { return lIter.getPtr() >= rIter.getPtr(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator>=(const ft::VectorIterator<T> lIter, const ft::VectorIterator<T_c> rIter) { return lIter.getPtr() >= rIter.getPtr(); }

	template <typename T>	// n + iter
	ft::VectorIterator<T> operator+(typename ft::VectorIterator<T>::difference_type n, const ft::VectorIterator<T> &iter) { return iter + n; }

	template <typename T>	// iterator - iterator
	typename ft::VectorIterator<T>::difference_type operator-(const ft::VectorIterator<T> &lIter, const ft::VectorIterator<T> &rIter) { return lIter.getPtr() - rIter.getPtr(); }

	template <typename T, typename T_c>	// iterator - const_iterator
	typename ft::VectorIterator<T>::difference_type operator-(const ft::VectorIterator<T> &lIter, const ft::VectorIterator<T_c> &rIter) { return lIter.getPtr() - rIter.getPtr(); }
}	// namespace ft

#endif
