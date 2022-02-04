#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "MapIterator.hpp"

namespace ft
{
	/**
	 * @brief map class
	 * 
	 * @tparam Key			Type of the keys.(key_type)
	 * @tparam T				Type of the mapped value.(mapped_type)
	 * @tparam Compare	A binary predicate that takes two element keys as arguments and returns a bool.(key_compare)
	 * @tparam Alloc		Type of the allocator object used to define the storage allocation model.(allocator_type)
	 */
	template < class Key, class T, class Compare = ft::less<Key>,
						class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map {
	public :
		/**
		 * @brief Member types
		 */
		typedef Key																		key_type;
		typedef T																			mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare																key_compare;

		template <class Key, class T, class Compare, class Alloc>
		class value_compare : binary_function<value_type, value_type, bool> {
			friend class map>
		
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		
		public:
			typedef bool				result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
		};

		typedef Alloc																			allocator_type;
		typedef allocator_type::reference									reference;
		typedef allocator_type::const_reference						const_reference;
		typedef allocator_type::pointer										pointer;
		typedef allocator_type::const_pointer							const_pointer;
		typedef ft::MapIterator<value_type>								iterator;
		typedef ft::MapIterator<const value_type>					const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type				size_type;

		/**
		 * @brief Member functions
		 */
		// Empty constructor
		explicit map (const key_compare& comp = key_compare(),
									const allocator_type& alloc = allocator_type());

		// Range constructor
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type());

		// Copy constructor
		map (const map& x);

		// Destructor
		~map();

		// Assignment operator
		map& operator=(const map& x);

		// Iterators:
		iterator 				begin();
		const_iterator	begin() const;
		iterator				end();
		const_iterator	end() const;
		reverse_iterator 				rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator				rend();
		const_reverse_iterator	rend() const;
		// Capacity:
		
	};
} // namespace ft

#endif
