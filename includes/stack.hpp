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

	protected :
		container_type _c;
	};

} // namespace ft

#endif
