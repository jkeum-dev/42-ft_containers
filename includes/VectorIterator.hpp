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

		// Default constructor
		VectorIterator(pointer ptr = ft_nullptr) : _current(ptr) {}

		// Copy constructor
		VectorIterator(const VectorIterator& copy) : _current(copy._current) {}

		// Assignment operator
		VectorIterator& operator=(const VectorIterator& copy) { if (this != &copy) this->_current = copy._current; return *this; }

		// Destructor
		virtual ~VectorIterator() {}

		// Getter
		pointer const & base() const { return _current; }

		// Overloading type casts
		operator VectorIterator<const T>() const { return VectorIterator<const T>(_current); }

		/**
		 * @brief Operators
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
	 * @brief Relational operators
	 */
	template <typename T>
	bool operator==(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator==(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename T>
	bool operator!=(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator!=(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename T>
	bool operator<(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator<(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename T>
	bool operator>(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator>(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename T>
	bool operator<=(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() <= rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator<=(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() <= rIter.base(); }
	
	template <typename T>
	bool operator>=(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() >= rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	bool operator>=(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() >= rIter.base(); }

	// n + iter
	template <typename T>
	VectorIterator<T> operator+(typename VectorIterator<T>::difference_type n, const VectorIterator<T> &iter) { return VectorIterator<T>(iter + n); }

	// iterator - iterator
	template <typename T>
	typename VectorIterator<T>::difference_type operator-(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() - rIter.base(); }

	// iterator - const_iterator
	template <typename T, typename T_c>
	typename VectorIterator<T>::difference_type operator-(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() - rIter.base(); }
}	// namespace ft

#endif
