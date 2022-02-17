#ifndef MAP_HPP
#define MAP_HPP

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

		class value_compare : binary_function<value_type, value_type, bool> {
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
		
		public:
			typedef bool				result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			value_compare() : comp() {}
			bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
		};

		typedef Alloc																															allocator_type;
		typedef typename allocator_type::reference																reference;
		typedef typename allocator_type::const_reference													const_reference;
		typedef typename allocator_type::pointer																	pointer;
		typedef typename allocator_type::const_pointer														const_pointer;
		typedef ft::MapIterator<value_type, value_type*, value_type&>							iterator;
		typedef ft::MapIterator<value_type, const value_type*, const value_type&>	const_iterator;
		typedef ft::reverse_iterator<iterator>																		reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>															const_reverse_iterator;
		typedef typename allocator_type::difference_type													difference_type;
		typedef typename allocator_type::size_type																size_type;
		typedef ft::RBTree<value_type, value_compare>															rb_tree;
		typedef ft::RBTreeNode<value_type>																				node_type;

		/**
		 * @brief Member functions
		 */
		// Empty constructor
		explicit map (const key_compare& comp = key_compare(),
									const allocator_type& alloc = allocator_type())
									: _alloc(alloc), _tree(), _comp(comp) {}

		// Range constructor
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = ft_nullptr)
				: _alloc(alloc), _tree(), _comp(comp) { insert(first, last); }

		// Copy constructor
		map (const map& x) : _alloc(x._alloc), _tree(), _comp(x._comp) { *this = x; }

		// Destructor
		~map() {}

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
		mapped_type& operator[](const key_type& k) {
			return (*(_tree.insert(make_pair(k, mapped_type())).first)).value->second;
		}
		pair<iterator, bool>	insert(const value_type& val) {
			ft::pair<node_type*, bool> res = _tree.insert(val);
			return ft::make_pair(iterator(res.first), res.second);
		}	// single element
		iterator							insert(iterator position, const value_type& val) {
			return iterator(_tree.insert(val, position).first);
		}	// with hint
		template <class InputIterator>
		void									insert(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = ft_nullptr) {
			while (first != last)
				_tree.insert(*first++);
		}	// range
		void			erase(iterator position) { _tree.erase(position.base()); }
		size_type	erase(const key_type& k) { return _tree.erase(_tree.find(value_type(k, mapped_type()))); }
		void			erase(iterator first, iterator last) {
			while (first != last)
				_tree.erase(*first++);
		}
		void swap(map& x) {
			_tree.swap(x._tree);
			allocator_type tmp_alloc = _alloc;
			_alloc = x._alloc;
			x._alloc = tmp_alloc;
			key_compare tmp_comp = _comp;
			_comp = x._comp;
			x._comp = tmp_comp;
		}
		void clear() { _tree.clear(); }
		// Observers:
		key_compare		key_comp() const { return key_compare(); }
		value_compare	value_comp() const { return value_compare(); }
		// Operations:
		iterator				find(const key_type& k) { return iterator(_tree.find(value_type(k, mapped_type()))); }
		const_iterator	find(const key_type& k) const { return const_iterator(_tree.find(value_type(k, mapped_type()))); }
		size_type				count(const key_type& k) const { if (_tree.find(value_type(k, mapped_type()))) return 1; else return 0; }
		iterator				lower_bound(const key_type& k) { return iterator(_tree.lower_bound(value_type(k, mapped_type()))); }
		const_iterator	lower_bound(const key_type& k) const { return const_iterator(_tree.lower_bound(value_type(k, mapped_type()))); }
		iterator				upper_bound(const key_type& k) { return iterator(_tree.upper_bound(value_type(k, mapped_type()))); }
		const_iterator	upper_bound(const key_type& k) const { return const_iterator(_tree.upper_bound(value_type(k, mapped_type()))); }
		pair<iterator, iterator>							equal_range(const key_type& k) { return ft::make_pair(lower_bound(k), upper_bound(k)); }
		pair<const_iterator, const_iterator>	equal_range(const key_type& k) const { return ft::make_pair(lower_bound(k), upper_bound(k)); }
		// Allocator:
		allocator_type get_allocator() const { return _alloc; }

		void showTree() { _tree.showMap(); }

		/**
		 * @brief Member variables
		 */
	private:
		allocator_type	_alloc;
		rb_tree					_tree;
		key_compare			_comp;
	};
} // namespace ft

#endif
