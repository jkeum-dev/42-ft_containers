#ifndef RBTREEBASE_HPP
#define RBTREEBASE_HPP

namespace ft
{
	enum RBColor { RED = false, BLACK = true };

	template <typename T>
	struct RBTreeNode {
	public :
		typedef T value_type;
		typedef RBTreeNode* node;
		node left_child;
		node right_child;
		node parent;
		RBColor colors;
	};
} // namespace ft

#endif
