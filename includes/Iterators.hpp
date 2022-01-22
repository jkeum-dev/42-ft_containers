#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <cstddef>

namespace ft
{
	/**
	 * @defgroup iterator_tags
	 * These are empty types, used to distinguish different iterators.
	 * The distinction is not made by what they contain, but simply by what they are.
	 * Different underlying algorithms can then be used based on the
	 * different operations supported by different iterator types.
	**/
	struct input_iterator_tag {};		// Marking input iterators.
	struct output_iterator_tag {};	// Marking output iterators.
	struct forward_iterator_tag : public input_iterator_tag {};								// Forward iterators support a superset of input iterator operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag {};				// Bidirectional iterators support a superset of forward iterator operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};	// Random-access iterators support a superset of bidirectional iterator operations.

	/**
	 * @brief iterator traits
	 * Traits class defining properties of iterators.
	 */
	// Generic Definition
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::value_type					value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::pointer						pointer;
		typedef typename Iterator::reference					reference;
	};

	// T* specialization
	template <class T>
	struct iterator_traits<T*> {
		typedef T														value_type;
		typedef ptrdiff_t										difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef T*													pointer;
		typedef T&													reference;
	};

	// const T* specialization
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
	 * This is a base class template that can be used to derive iterator classes from it.
	 * It is not an iterator class and does not provide any of the functionality an iterator is expected to have.
	 * 
	 * @tparam Category		Category to which the iterator belongs to.
	 * @tparam T					Type of elements pointed by the iterator.
	 * @tparam Distance		Type to represent the difference between two iterators.
	 * @tparam Pointer		Type to represent a pointer to an element pointed by the iterator.
	 * @tparam Reference	Type to represent a reference to an element pointed by the iterator.
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
	 * This class reverses the direction in which a bidirectional or random-access iterator iterates through a range.
	 * 
	 * @tparam Iterator		A bidirectional iterator type. Or a random-access iterator,
	 * 										if an operator that requires such a category of iterators is used.
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
		reference operator*() const { iterator_type tmp = current; return *--tmp; }
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }
		reverse_iterator& operator++() { --current; return *this; }
		reverse_iterator  operator++(int) { reverse_iterator temp = *this; ++(*this); return temp; }
		reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
		reverse_iterator& operator--() { ++current; return *this; }
		reverse_iterator  operator--(int) { reverse_iterator temp = *this; --(*this); return temp; }
		reverse_iterator& operator-=(difference_type n) { current += n; return *this; }
		pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type n) const { return base()[-n - 1]; }
	};

	/**
	 * @brief Non-member function overloads
	**/
	template <typename Iterator>
	bool operator==(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator==(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator_c>& rIter) { return lIter.base() == rIter.base(); }
	
	template <typename Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator!=(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator_c>& rIter) { return lIter.base() != rIter.base(); }
	
	template <typename Iterator>
	bool operator<(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator<(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator_c>& rIter) { return lIter.base() > rIter.base(); }
	
	template <typename Iterator>
	bool operator>(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator>(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator_c>& rIter) { return lIter.base() < rIter.base(); }
	
	template <typename Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator>& rIter) { return lIter.base() >= rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator<=(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator_c>& rIter) { return lIter.base() >= rIter.base(); }
	
	template <typename Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator>& rIter) { return lIter.base() <= rIter.base(); }
	
	template <typename Iterator, typename Iterator_c>	// compare with const_iterator
	bool operator>=(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator_c>& rIter) { return lIter.base() <= rIter.base(); }

	// n + iter
	template <typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &iter) { return iter + n; }

	// iterator - iterator
	template <typename Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator>& rIter) { return rIter.base() - lIter.base(); }

	// iterator - const_iterator
	template <typename Iterator, typename Iterator_c>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lIter, const reverse_iterator<Iterator_c>& rIter) { return rIter.base() - lIter.base(); }

}	// namespace ft

#endif
