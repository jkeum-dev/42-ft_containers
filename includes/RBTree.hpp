#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <stdexcept>
#include "MapIterator.hpp"

namespace ft
{
	template < typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
	class RBTree {
	public :
		/**
		 * @brief Member types
		 */
		typedef T																									value_type;
		typedef T*																								pointer;
		typedef const T*																					const_pointer;
		typedef T&																								reference;
		typedef const T&																					const_reference;
		typedef Compare																						value_comp;
		typedef Alloc																							allocator_type;
		typedef size_t																						size_type;
		typedef ft::RBTreeNode<T>																	node_type;
		typedef ft::MapIterator<T>																iterator;
		typedef ft::MapIterator<const T>													const_iterator;
		typedef typename Alloc::template rebind<node_type>::other node_allocator_type;

		/**
		 * @brief Member variables
		 */
	private :
		node_type*					_root;
		node_type*					_nil;
		size_type						_size;
		value_comp					_comp;
		node_allocator_type	_node_alloc;
	};
} // namespace ft


#endif
