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

		VectorIterator(pointer ptr = ft_nullptr) : _current(ptr) {}					// Default constructor
		VectorIterator(const VectorIterator& copy) : _current(copy._current) {}	// Copy constructor
		VectorIterator& operator=(const VectorIterator& copy) { if (this != &copy) this->_current = copy._current; return *this; }	// Assignment operator
		virtual ~VectorIterator() {}	// Destructor
		pointer const & base() const { return _current; }	// getter

		operator VectorIterator<const T>() const { return VectorIterator<const T>(_current); }

		/**
		 * @brief operators
		 */
		reference operator*() const { return *_current;}
		pointer operator->() const { return _current; }
		VectorIterator& operator++() { ++_current; return *this; }
		VectorIterator operator++(int) { VectorIterator tmp = *this; ++_current; return tmp; }
		VectorIterator& operator--() { --_current; return *this; }
		VectorIterator operator--(int) { VectorIterator tmp = *this; --_current; return tmp; }
		VectorIterator operator+(difference_type n) const { return VectorIterator(_current + n); }	// iter + n
		VectorIterator operator-(difference_type n) const { return VectorIterator(_current - n); }	// iter - n
		VectorIterator& operator+=(difference_type n) { _current += n; return *this; }
		VectorIterator& operator-=(difference_type n) { _current -= n; return *this; }
		reference operator[](difference_type n) const { return *(_current + n); }

	protected :
		pointer _current;
	};

	/**
	 * @brief operators
	 */
	template <typename T>
	bool operator==(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator==(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T_c>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename T>
	bool operator!=(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator!=(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T_c>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename T>
	bool operator<(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator<(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T_c>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename T>
	bool operator>(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator>(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T_c>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename T>
	bool operator<=(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T>& rIter) { return lIter.base() <= rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator<=(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T_c>& rIter) { return lIter.base() <= rIter.base(); }
	
	template <typename T>
	bool operator>=(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T>& rIter) { return lIter.base() >= rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator>=(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T_c>& rIter) { return lIter.base() >= rIter.base(); }

	template <typename T>	// n + iter
	ft::VectorIterator<T> operator+(typename ft::VectorIterator<T>::difference_type n, const ft::VectorIterator<T> &iter) { return ft::VectorIterator<T>(iter + n); }

	template <typename T>	// iterator - iterator
	typename ft::VectorIterator<T>::difference_type operator-(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T>& rIter) { return lIter.base() - rIter.base(); }

	template <typename T, typename T_c>	// iterator - const_iterator
	typename ft::VectorIterator<T>::difference_type operator-(const ft::VectorIterator<T>& lIter, const ft::VectorIterator<T_c>& rIter) { return lIter.base() - rIter.base(); }
}	// namespace ft

#endif
