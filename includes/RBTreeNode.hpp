#ifndef RBTREENODE_HPP
#define RBTREENODE_HPP

#include <memory>

namespace ft
{
	enum RBColor { RED = false, BLACK = true };

	template < typename T, typename Alloc = std::allocator<T> >
	struct RBTreeNode {
	public :
		typedef T						value_type;
		typedef RBTreeNode*	node;

		T*			value;
		node		left_child;
		node		right_child;
		node		parent;
		RBColor	color;
		Alloc		alloc;

		RBTreeNode() : value(ft_nullptr), left_child(ft_nullptr), right_child(ft_nullptr),
									parent(ft_nullptr), color(BLACK), alloc(Alloc()) {}

		RBTreeNode(const T& val) : value(ft_nullptr), left_child(ft_nullptr), right_child(ft_nullptr),
															parent(ft_nullptr), color(RED), alloc(Alloc()) {
			value = alloc.allocate(1);
			alloc.construct(value, val);
		}

		RBTreeNode(const RBTreeNode& copy) : value(ft_nullptr), left_child(ft_nullptr), right_child(ft_nullptr),
																				parent(ft_nullptr), color(RED), alloc(Alloc()) {
			if (copy.value != ft_nullptr) {
				value = alloc.allocate(1);
				alloc.construct(value, *copy.value);
				color = copy.color;
			}
		}

		~RBTreeNode() {
			if (value != ft_nullptr) {
				alloc.destroy(value);
				alloc.deallocate(value, 1);
			}
		}
	};
} // namespace ft

#endif
