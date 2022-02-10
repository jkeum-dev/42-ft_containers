#ifndef UTILS_HPP
#define UTILS_HPP

#include "Iterators.hpp"

namespace ft
{
	/**
	 * @brief nullptr_t
	 * Type of the null pointer constant nullptr.
	 * This is a const global object.
	 */
	const class nullptr_t{
	public:
		// Convertible to any type of null non-member pointer,
		template<class T>
		operator T*() const { return 0; }

		// or any type of null member pointer.
		template<class C, class T>	// any type T for any class type C
		operator T C::*() const { return 0; }

	private:
		void operator&() const;	// Can't take address of nullptr.
	} ft_nullptr = {};

	/**
	 * @brief enable_if
	 * At this time, we pass the condition we want to check to part B.
	 * If B is evaluated as true, the type of enable_if::value becomes T.
	 * And if B is false, value does not exist in enable_if.
	 * 
	 * @tparam B	is_bool
	 * @tparam T	type
	 */
	template <bool Cond, typename T = void>
	struct enable_if {};

	/**
	 * @brief enable_if
	 * When B is true, type is defined in the specialized version.
	 * And in other cases, nothing is defined inside it.
	 * 
	 * @tparam T	type
	 */
	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	/**
	 * @brief true_type / false_type
	 * It acts like an interface so that the value is not displayed every time.
	 */
	struct true_type { enum _value { value = true }; };
	struct false_type { enum _value { value = false }; };

	/**
	 * @brief remove_const
	 * Remove const from template type.
	 * This is a specialization so that only T can be imported from const T.
	 * 
	 * @tparam T	type
	 */
	template <typename T>
	struct remove_const { typedef T type; };
	template <typename T>
	struct remove_const<T const> { typedef T type; };

	/**
	 * @brief remove_volatile
	 * Remove volatile from template type.
	 * This is a specialization so that only T can be imported from volatile T.
	 * 
	 * @tparam T	type
	 */
	template <typename T>
	struct remove_volatile { typedef T type; };
	template <typename T>
	struct remove_volatile<T volatile> { typedef T type; };

	/**
	 * @brief remove_cv
	 * Remove const and volatile from template type.
	 * 
	 * @tparam T	type
	 */
	template <typename T>
	struct remove_cv { typedef typename remove_const<typename remove_volatile<T>::type>::type type; };

	/**
	 * @brief is_integral_helper
	 * Declare a meta function to remove the const qualifier.
	 */
	template <typename T>
	struct is_integral_helper : false_type {};

	/**
	 * @brief 
	 * After define so that specialization can be easily made into a macro,
	 * the integral type is specialized.
	 */
	#define IS_INTEGRAL_SPECIALIZATION(T) template<> struct is_integral_helper<T> : true_type {}

	IS_INTEGRAL_SPECIALIZATION(bool);
	IS_INTEGRAL_SPECIALIZATION(char);
	IS_INTEGRAL_SPECIALIZATION(signed char);
	IS_INTEGRAL_SPECIALIZATION(short int);
	IS_INTEGRAL_SPECIALIZATION(int);
	IS_INTEGRAL_SPECIALIZATION(long int);
	IS_INTEGRAL_SPECIALIZATION(long long int);
	IS_INTEGRAL_SPECIALIZATION(unsigned char);
	IS_INTEGRAL_SPECIALIZATION(unsigned short int);
	IS_INTEGRAL_SPECIALIZATION(unsigned int);
	IS_INTEGRAL_SPECIALIZATION(unsigned long int);
	IS_INTEGRAL_SPECIALIZATION(unsigned long long int);

/**
 * @brief is_integral
 * Identifies whether T is an integral type.
 * It inherits is_integral_helper<T> and has a different type according to T.
 * Whether the const and volatile qualifier is attached or not,
 * it does not change whether it is an integral type or not, so remove it and pass it over.
 * 
 * @tparam T	type
 */
	template <typename T>
	struct is_integral : public is_integral_helper<typename remove_cv<T>::type> {};

	/**
	 * @brief equal
	 * Test whether the elements in two ranges are equal.
	 * 
	 * @tparam InputIterator1		first sequence
	 * @tparam InputIterator2		second sequence
	 * @tparam BinaryPredicate	binary function
	 * @param first1	initial position of first sequence
	 * @param last1		final position of first sequence
	 * @param first2	initial position of second sequence
	 * @param pred		Accepts two elements as argument
	 * 								(one of each of the two sequences, in the same order),
	 * 								and returns a value convertible to bool.
	 * @return true		All of the elements in both ranges match.
	 * @return false	Not true.
	 */
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}	// equality

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
						InputIterator2 first2, BinaryPredicate pred) {
		while (first1 != last1) {
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}	// predicate

	/**
	 * @brief lexicographical_compare
	 * Lexicographical less-than comparison.
	 * 
	 * @tparam InputIterator1		first sequence
	 * @tparam InputIterator2		second sequence
	 * @tparam Compare					binary function
	 * @param first1	initial position of first sequence
	 * @param last1		final position of first sequence
	 * @param first2	initial position of second sequence
	 * @param last2		final position of second sequence
	 * @param comp		Accepts two arguments of the types pointed by the iterators,
	 * 								and returns a value convertible to bool.
	 * @return true		If the first range compares lexicographically less than the second.
	 * @return false	Not true(including when all the elements of both ranges are equivalent).
	 */
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
															InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}	// default

	template <typename InputIterator1, typename InputIterator2, typename Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
															InputIterator2 first2, InputIterator2 last2,
															Compare comp) {
		while (first1 != last1) {
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}	// custom

	/**
	 * @brief binary_function
	 * Binary function object base class.
	 * 
	 * @tparam Arg1		Type of the first argument in member operator()
	 * @tparam Arg2		Type of the second argument in member operator()
	 * @tparam Result	Type returned by member operator()
	 */
	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	/**
	 * @brief less
	 * Function object class for less-than inequality comparison.
	 * 
	 * @tparam T	Type of the arguments to compare by the functional call.
	 */
	template <class T>
	struct less : binary_function<T, T, bool> {
		bool operator()(const T& x, const T& y) const { return x < y; }
	};

	/**
	 * @brief pair
	 * 
	 * @tparam T1	Type of member first
	 * @tparam T2	Type of member second
	 */
	template <class T1, class T2>
	struct pair {
	public :
		/**
		 * @brief Member types
		 */
		typedef T1 first_type;
		typedef T2 second_type;

		/**
		 * @brief Member variables
		 */
		first_type	first;
		second_type	second;

		/**
		 * @brief Member functions
		 */
		// Default constructor
		pair() : first(), second() {}

		// Copy constructor
		template <class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

		// Initialization constructor
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator=(const pair& pr) {
			if (*this == pr)
				return *this;
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};

	// Relational operators
	template <class T1, class T2>
	inline bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	inline bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return !(lhs == rhs); }

	template <class T1, class T2>
	inline bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	inline bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs < lhs); }

	template <class T1, class T2>
	inline bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs < lhs; }

	template <class T1, class T2>
	inline bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs < rhs); }

	/**
	 * @brief make_pair
	 * Construct pair object.
	 * 
	 * @tparam T1		Type of member first of pair
	 * @tparam T2		Type of member second of pair
	 * @param x			Values for the members first
	 * @param y			Values for the members second
	 * @return pair<T1, T2>		A pair object whose elements first and second are set to x and y respectivelly.
	 */
	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

	/**
	 * @brief distance
	 * User-defined function for finding the distance between two iterators.
	 * 
	 * @tparam InputIterator		iterator type
	 * @param first		initial position of the iterator
	 * @param last		final position of the iterator
	 * @return iterator_traits<InputIterator>::difference_type	distance between two iterators
	 */
	template <typename InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
		typename ft::iterator_traits<InputIterator>::difference_type n = 0;
		while (first++ != last)
			n++;
		return n;
	}
} // namespace ft

#endif
