#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#include "Iterators.hpp"
#include "utils.hpp"
#include "RBTreeNode.hpp"

namespace ft
{
	template <typename T>
	class MapIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	public :
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type				value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer						pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference					reference;
		typedef ft::RBTreeNode<T>																														node_type;

		MapIterator(node_type* ptr = ft_nullptr) : _node(ptr) {}	// Default constructor
		MapIterator(const MapIterator& copy) : _node(copy._node) {}	// Copy constructor
		MapIterator& operator=(const MapIterator& copy) { if (this != &copy) this->_node = copy._node; return *this; }	// Assignment operator
		virtual ~MapIterator() {}	// Destructor
		node_type* const & base() const { return _node; }	// Getter
		operator MapIterator<const T>() const { return MapIterator<const T>(_node); }	// Overloading type casts

		/**
		 * @brief Operators
		 */
		reference operator*() const { return *_node->value; }
		pointer operator->() const { return _node->value; }

		MapIterator& operator++() {
			node_type* tmp = ft_nullptr;
			// if right_child exists,
			if (_node->right_child->value != ft_nullptr) {
				tmp = _node->right_child;
				// search the leftmost of the right_child.
				while (tmp->left_child->value != ft_nullptr)
					tmp = tmp->left_child;
			}
			else {	// if right_child doesn't exist,
				tmp = _node->parent;
				// if current node is right_child,
				if (tmp->right_child == _node) {
					node_type* tmp_parent = ft_nullptr;
					while (true) {
						tmp_parent = tmp->parent;
						if (tmp_parent->value == ft_nullptr)	// tmp is root
							break;
						if (tmp_parent->right_child == tmp)
							break;
						tmp = tmp->parent;
					}
					// tmp is left_child or root-node.
					if (tmp->parent->value != ft_nullptr)
						tmp = tmp->parent;
				}
			}
			_node = tmp;
			return *this;
		}
		MapIterator operator++(int) { MapIterator tmp = *this; ++_node; return tmp; }

		MapIterator& operator--() {
			node_type* tmp = ft_nullptr;
			if (_node == ft_nullptr)
				tmp = _node->parent;
			else if (_node->left_child != ft_nullptr) {	// if left_child exists,
				tmp = _node->left_child;
				// search the rightmost of the left_child.
				while (tmp->right_child != ft_nullptr)
					tmp = tmp->right_child;
			}
			else {	// if left_child doesn't exist,
				tmp = _node->parent;
				// if current node is left_child,
				if (tmp->left_child == _node) {
					node_type* tmp_parent;
					while (true) {
						tmp_parent = tmp->parent;
						if (tmp_parent->value == ft_nullptr)	// tmp is root
							break;
						if (tmp_parent->left_child == tmp)
							break;
						tmp = tmp->parent;
					}
					// tmp is right_child or root-node.
					if (tmp->parent->value != ft_nullptr)
						tmp = tmp->parent;
				}
			}
			_node = tmp;
			return *this;
		}
		MapIterator operator--(int) { MapIterator tmp = *this; --_node; return tmp; }

	protected :
		node_type* _node;
	};

	/**
	 * @brief Relational operators
	 */
	template <typename T>
	bool operator==(const MapIterator<T>& lIter, const MapIterator<T>& rIter) { return lIter.base()->value == rIter.base()->value; }

	template <typename T, typename T_c>	// compare with const_iterator
	bool operator==(const MapIterator<T>& lIter, const MapIterator<T_c>& rIter) { return lIter.base()->value == rIter.base()->value; }

	template <typename T>
	bool operator!=(const MapIterator<T>& lIter, const MapIterator<T>& rIter) { return lIter.base()->value != rIter.base()->value; }

	template <typename T, typename T_c>	// compare with const_iterator
	bool operator!=(const MapIterator<T>& lIter, const MapIterator<T_c>& rIter) { return lIter.base()->value != rIter.base()->value; }
} // namespace ft


#endif
