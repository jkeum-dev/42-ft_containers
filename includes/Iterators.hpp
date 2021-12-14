#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <cstddef>

namespace ft {
	/**
	 *  @defgroup iterator_tags Iterator Tags
	 *  These are empty types, used to distinguish different iterators.  The
	 *  distinction is not made by what they contain, but simply by what they
	 *  are.  Different underlying algorithms can then be used based on the
	 *  different operations supported by different iterator types.
	**/
	//  Marking input iterators.
	struct input_iterator_tag {};
	//  Marking output iterators.
	struct output_iterator_tag {};
	// Forward iterators support a superset of input iterator operations.
	struct forward_iterator_tag : public input_iterator_tag {};
	// Bidirectional iterators support a superset of forward iterator operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	// Random-access iterators support a superset of bidirectional iterator operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class T>
	struct iterator_traits {
		typedef typename T::value_type			value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::iterator_category	iterator_category;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef T*							pointer;
		typedef T&							reference;
	};

	template <class T>
	struct iterator_traits<const T*> {
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};
}	// namespace ft

#endif
