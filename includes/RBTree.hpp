#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "MapIterator.hpp"

namespace ft
{
	template < typename T, typename Compare = ft::less<Key>, typename Alloc = std::allocator<T> >
	class RBTree {
	public :
		typedef T					value_type;
		typedef T*				pointer;
		typedef const T*	const_pointer;
		typedef T&				reference;
		typedef const T&	const_reference;
		typedef Compare		value_comp;
		typedef Alloc			allocator_type;
		typedef size_t		size_type;
		typedef ft::RBTreeNode<T>					node_type;
		typedef ft::MapIterator<T>				iterator;
		typedef ft::MapIterator<const T>	const_iterator;
		typedef typename Alloc::template rebind<node_type>::other node_allocator_type;

		
	};
} // namespace ft


#endif
