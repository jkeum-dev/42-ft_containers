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
	struct input_iterator_tag {};		// Marking input iterators.
	struct output_iterator_tag {};	// Marking output iterators.
	struct forward_iterator_tag : public input_iterator_tag {};								// Forward iterators support a superset of input iterator operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag {};				// Bidirectional iterators support a superset of forward iterator operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};	// Random-access iterators support a superset of bidirectional iterator operations.

	/**
	 * @brief iterator traits
	 */
	template <class T>
	struct iterator_traits {
		typedef typename T::value_type				value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::iterator_category	iterator_category;
		typedef typename T::pointer						pointer;
		typedef typename T::reference					reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef T														value_type;
		typedef ptrdiff_t										difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef T*													pointer;
		typedef T&													reference;
	};

	template <class T>
	struct iterator_traits<const T*> {
		typedef T														value_type;
		typedef ptrdiff_t										difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef const T*										pointer;
		typedef const T&										reference;
	};

	/**
	 * @brief iterator
	 */
	template<class Category, class T, class Distance = ptrdiff_t,
					class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T					value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	/**
	 * @brief reverse iterator
	 * https://www.cplusplus.com/reference/iterator/reverse_iterator/
	 */
	template <typename Iterator>
	class reverse_iterator
	{
	protected:
		Iterator	current;

	public:
		typedef Iterator																							iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type				value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer						pointer;
		typedef typename iterator_traits<Iterator>::reference					reference;

		/**
		 * @brief Member functions
		 */
		reverse_iterator() : current() {}	// (1) default constructor
		explicit reverse_iterator(iterator_type it) : current(it) {}	// (2) initalization constructor
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) {}	// (3) copy / type-cast constructor
		iterator_type base() const { return current; }
		reference operator*() const { return *current; }
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }
		reverse_iterator& operator++() { --current; return *this; }
		reverse_iterator  operator++(int) { reverse_iterator temp = *this; ++(*this); return temp; }
		reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
		reverse_iterator& operator--() { ++current; return *this; }
		reverse_iterator  operator--(int) { reverse_iterator temp = *this; --(*this); return temp; }
		reverse_iterator& operator-=(difference_type n) { current += n; return *this; }
		pointer operator->() const { return current; }
		reference operator[](difference_type n) const { return *(current + n); }
	};

	/**
	 * @brief Non-member function overloads
	**/
	template <typename Iterator>
	bool operator==(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator==(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator_c>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename Iterator>
	bool operator!=(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator!=(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator_c>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename Iterator>
	bool operator<(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator<(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator_c>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename Iterator>
	bool operator>(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator>(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator_c>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename Iterator>
	bool operator<=(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator>& rIter) { return lIter.base() <= rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator<=(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator_c>& rIter) { return lIter.base() <= rIter.base(); }
	
	template <typename Iterator>
	bool operator>=(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator>& rIter) { return lIter.base() >= rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator>=(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator_c>& rIter) { return lIter.base() >= rIter.base(); }

	template <typename Iterator>	// n + iter
	ft::reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator> &iter) { return ft::reverse_iterator<Iterator>(iter + n); }

	template <typename Iterator>	// iterator - iterator
	typename ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator>& rIter) { return lIter.base() - rIter.base(); }

	template <typename Iterator, typename Iterator_c>	// iterator - const_iterator
	typename ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator>& lIter, const ft::reverse_iterator<Iterator_c>& rIter) { return lIter.base() - rIter.base(); }

}	// namespace ft

#endif
