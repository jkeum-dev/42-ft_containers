#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	/**
	 * @brief stack class
	 * 
	 * @tparam T					Type of the elements.(value_type)
	 * @tparam Container	Type of the internal underlying container object.(container_type)
	 */
	template < class T, class Container = ft::vector<T> >
	class stack {
	public :
		/**
		 * @brief Member types
		 */
		typedef T					value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		/**
		 * @brief Member functions
		 */
		explicit stack (const container_type& ctnr = container_type()) : _c(ctnr) {}
		bool empty() const { return _c.empty(); }
		size_type size() const { return _c.size(); }
		value_type& top() { return _c.back(); }
		const value_type& top() const { return _c.back(); }
		void push (const value_type& val) { _c.push_back(val); }
		void pop() { _c.pop_back(); }

		// friend function for direct access to member variables of a class
		template <class _T, class _Container>
		friend bool operator==(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
		friend bool operator<(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

	protected :
		container_type _c;
	};

	// Relational operators
	template <class T, class Container>
	inline bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs._c == rhs._c; }

	template <class T, class Container>
	inline bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs == rhs); }

	template <class T, class Container>
	inline bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs._c < rhs._c; }

	template <class T, class Container>
	inline bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(rhs < lhs); }

	template <class T, class Container>
	inline bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return rhs < lhs; }

	template <class T, class Container>
	inline bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs < rhs); }
} // namespace ft

#endif
