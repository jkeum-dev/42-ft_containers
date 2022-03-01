#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	/**
	 * @brief VectorIterator
	 * Implemented for use as a random access iterator.
	 * Random access iterators are iterators that can be used to access elements
	 * at an arbitrary offset position relative to the element they point to,
	 * offering the same functionality as pointers.
	 * 
	 * @tparam T	Type of elements pointed by the iterator.
	 */
	template <typename T>
	class VectorIterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
	public :
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type				value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer						pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference					reference;

		VectorIterator(pointer ptr = ft_nullptr) : _current(ptr) {}	// Default constructor
		VectorIterator(const VectorIterator<T>& copy) : _current(copy.base()) {}	// Copy constructor
		VectorIterator& operator=(const VectorIterator<T>& copy) { if (this != &copy) this->_current = copy.base(); return *this; }	// Assignment operator
		virtual ~VectorIterator() {}	// Destructor
		pointer const & base() const { return _current; }	// Getter
		operator VectorIterator<const T>() const { return VectorIterator<const T>(_current); }	// Overloading type casts

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
	inline bool operator==(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	inline bool operator==(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename T>
	inline bool operator!=(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	inline bool operator!=(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename T>
	inline bool operator<(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	inline bool operator<(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename T>
	inline bool operator>(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	inline bool operator>(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename T>
	inline bool operator<=(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() <= rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	inline bool operator<=(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() <= rIter.base(); }
	
	template <typename T>
	inline bool operator>=(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() >= rIter.base(); }
	
	template <typename T, typename T_c>	// compare with const_iterator
	inline bool operator>=(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() >= rIter.base(); }

	// n + iter
	template <typename T>
	inline VectorIterator<T> operator+(typename VectorIterator<T>::difference_type n, const VectorIterator<T> &iter) { return VectorIterator<T>(iter + n); }

	// iterator - iterator
	template <typename T>
	inline typename VectorIterator<T>::difference_type operator-(const VectorIterator<T>& lIter, const VectorIterator<T>& rIter) { return lIter.base() - rIter.base(); }

	// iterator - const_iterator
	template <typename T, typename T_c>
	inline typename VectorIterator<T>::difference_type operator-(const VectorIterator<T>& lIter, const VectorIterator<T_c>& rIter) { return lIter.base() - rIter.base(); }
}	// namespace ft

#endif
