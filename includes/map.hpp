#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "RBTree.hpp"

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
		protected:
			Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		
		public:
			typedef bool				result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
		};

		typedef Alloc																						allocator_type;
		typedef allocator_type::reference												reference;
		typedef allocator_type::const_reference									const_reference;
		typedef allocator_type::pointer													pointer;
		typedef allocator_type::const_pointer										const_pointer;
		typedef ft::MapIterator<value_type>											iterator;
		typedef ft::MapIterator<const value_type>								const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename allocator_type::difference_type				difference_type;
		typedef typename allocator_type::size_type							size_type;
		typedef typename ft::RBTree<value_type, value_compare>	rb_tree;

		/**
		 * @brief Member functions
		 */
		// Empty constructor
		explicit map (const key_compare& comp = key_compare(),
									const allocator_type& alloc = allocator_type())
									: _alloc(alloc), _tree() {}

		// Range constructor
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _tree() { insert(first, last); }

		// Copy constructor
		map (const map& x) : _alloc(x._alloc), _tree() { *this = x; }

		// Destructor
		~map() { _tree.~RBTree(); }

		// Assignment operator
		map& operator=(const map& x) { if (this != x) _tree.copy(x._tree); return *this; }

		// Iterators:
		iterator 				begin() { return iterator(_tree.get_begin()); }
		const_iterator	begin() const { return const_iterator(_tree.get_begin()); }
		iterator				end() { return iterator(_tree.get_end()); }
		const_iterator	end() const { return const_iterator(_tree.get_end()); }
		reverse_iterator 				rbegin() { return reverse_iterator(_tree.get_end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(_tree.get_end()); }
		reverse_iterator				rend() { return reverse_iterator(_tree.get_begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(_tree.get_begin()); }
		// Capacity:
		bool			empty() const { return _tree.empty(); }
		size_type	size() const { return _tree.size(); }
		size_type max_size() const { return _alloc.max_size(); }
		// Element access:
		mapped_type& operator[] (const key_type& k) {
			return (*(_tree.insert(make_pair(k, mapped_type())).first)).second;
		}
		pair<iterator, bool> insert(const value_type& val) {
			ft::pair<node_type*, bool> res = _tree.insert(val);
			return ft::make_pair(iterator(res.first), res.second);
		}	// single element
		iterator insert(iterator position, const value_type& val) {
			return iterator(_tree.insert(val, position).first);
		}	// with hint
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			while (first != last)
				_tree.insert(*first++);
		}	// range

		/**
		 * @brief Member variables
		 */
	private:
		allocator_type	_alloc;
		rb_tree					_tree;
	};
} // namespace ft

#endif
