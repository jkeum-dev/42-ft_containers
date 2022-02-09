#ifndef RBTREENODE_HPP
#define RBTREENODE_HPP

namespace ft
{
	enum RBColor { RED = false, BLACK = true };

	template <typename T>
	struct RBTreeNode {
	public :
		typedef T value_type;
		typedef RBTreeNode* node;
		T* value;
		node left_child;
		node right_child;
		node parent;
		RBColor color;
	};
} // namespace ft

#endif
