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
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

		VectorIterator(pointer ptr = ft_nullptr) : _ptr(ptr) {}					// Default constructor
		VectorIterator(const VectorIterator& copy) : _ptr(copy._ptr) {}	// Copy constructor
		VectorIterator& operator=(const VectorIterator& copy) {
			if (this != copy)
				this->_ptr = copy._ptr;
			return *this;
		}	// Assignment operator
		virtual ~VectorIterator() {}	// Destructor
		pointer const & getPtr() const { return this->_ptr; }	// getter

	private :
		pointer _ptr;
	};
}	// namespace ft

#endif
