#ifndef SET_HPP
#define SET_HPP

#include "RBTree.hpp"

namespace ft
{
	template < class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class set {
	public :
		/**
		 * @brief Member types
		 */
		typedef const T																			key_type;
		typedef const T																			value_type;
		typedef Compare																			key_compare;
		typedef Compare																			value_compare;
		typedef Alloc																				allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename ft::MapIterator<value_type, false>	iterator;
		typedef typename ft::MapIterator<value_type, true>	const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef typename allocator_type::difference_type		difference_type;
		typedef typename allocator_type::size_type					size_type;
		typedef ft::RBTree<value_type, value_compare>				rb_tree;
		typedef ft::RBTreeNode<value_type>									node_type;

		/**
		 * @brief Member functions
		 */
		// Empty constructor
		explicit set (const key_compare& comp = key_compare(),
									const allocator_type& alloc = allocator_type())
									: _alloc(alloc), _tree(), _comp(comp) {}

		// Range constructor
		template <class InputIterator>
		set (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = ft_nullptr)
				: _alloc(alloc), _tree(), _comp(comp) { insert(first, last); }

		// Copy constructor
		set (const set& x) : _alloc(x._alloc), _tree(), _comp(x._comp) { *this = x; }

		// Destructor
		~set() {}

		// Assignment operator
		set& operator=(const set& x) { if (this != &x) _tree.copy(x._tree); return *this; }

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
		pair<iterator, bool>	insert(const value_type& val) {
			ft::pair<node_type*, bool> res = _tree.insert(val);
			return ft::make_pair(iterator(res.first), res.second);
		}	// single element
		iterator							insert(iterator position, const value_type& val) {
			return iterator(_tree.insert(val, position.base()).first);
		}	// with hint
		template <class InputIterator>
		void									insert(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = ft_nullptr) {
			while (first != last)
				_tree.insert(*first++);
		}	// range
		void			erase(iterator position) { _tree.erase(position.base()); }
		size_type	erase(const value_type& val) { return _tree.erase(_tree.find(val)); }
		void			erase(iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}
		void swap(set& x) { _tree.swap(x._tree); }
		void clear() { _tree.clear(); }

		// Observers:
		key_compare		key_comp() const { return key_compare(); }
		value_compare	value_comp() const { return value_compare(); }

		// Operations:
		iterator	find(const value_type& val) const { return iterator(_tree.find(val)); }
		size_type	count(const value_type& val) const { if (_tree.find(val)->value != ft_nullptr) return 1; else return 0; }
		iterator	lower_bound(const value_type& val) const { return iterator(_tree.lower_bound(val)); }
		iterator	upper_bound(const value_type& val) const { return iterator(_tree.upper_bound(val)); }
		pair<iterator,iterator> equal_range(const value_type& val) const { return ft::make_pair(lower_bound(val), upper_bound(val)); }

		// Allocator:
		allocator_type get_allocator() const { return _alloc; }

		/**
		 * @brief Member variables
		 */
	private:
		allocator_type	_alloc;
		rb_tree					_tree;
		value_compare		_comp;
	};

	/**
	 * @brief Relational operators
	 */
	template <class T, class Compare, class Alloc>
	bool operator==(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Compare, class Alloc>
	bool operator!=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator<(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Compare, class Alloc>
	bool operator<=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator>(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class T, class Compare, class Alloc>
	bool operator>=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	// swap
	template <class T, class Compare, class Alloc>
	void swap(set<T, Compare, Alloc>& x, set<T, Compare, Alloc>& y) { x.swap(y); }
} // namespace ft

#endif
