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
		 * @brief Member functions
		 */
		// Default constructor
		RBTree() : _root(ft_nullptr), _nil(ft_nullptr), _size(0),
							_comp(value_comp()), _node_alloc(node_allocator_type()) {
			_nil = make_nil();
			_root = _nil;
		}

		// Copy constructor
		RBTree(const RBTree& _copy) : _root(ft_nullptr), _nil(ft_nullptr), _size(0),
																	_comp(value_comp()), _node_alloc(node_allocator_type()) {
			_nil = make_nil();
			clear();
			copy(_copy);
			_nil->parent = get_max_value_node();
		}

		// Destructor
		~RBTree() {
			clear();
			_node_alloc.destroy(_nil);
			_node_alloc.deallocate(_nil, 1);
		}

		// Assignment operator
		RBTree& operator=(const RBTree& x) { if (this != &x) { clear(); copy(x); } return *this; }

		// Iterators:
		node_type* get_begin() const {
			node_type* tmp = _root;
			while (tmp->left_child->value != ft_nullptr)
				tmp = tmp->left_child;
			return tmp;
		}
		node_type* get_end() const { return _nil; }

		// Capacity:
		bool empty() const { return _size == 0; }
		size_type size() const { return _size; }

		// Element access:
		ft::pair<node_type*, bool> insert(const value_type& val, node_type* hint = ft_nullptr) {
			node_type* new_node = make_node(val); // Creates a node with the val value entered as an argument.
			node_type* position = _root; // Where the node will be inserted.
			// If tree is empty.
			if (_size == 0) {
				_root = new_node;
				_root->left_child = _nil;
				_root->right_child = _nil;
				_root->parent = _nil;
				_root->color = BLACK;
				_nil->parent = _root;
				_size++;
				return ft::make_pair(_root, true);
			}
			// Check if the hint position is valid.
			if (hint != ft_nullptr && hint->value != ft_nullptr)
				position = check_hint(val, hint);
			// Find the position where the node will be inserted.
			ft::pair<node_type*, bool> is_valid = get_position(position, new_node);
			if (is_valid.second == false) {
				_node_alloc.destroy(new_node);
				_node_alloc.deallocate(new_node, 1);
				return is_valid;
			}
			// A new_node has been inserted,
			// and now we need to balance it according to the rules of the RBTree.
			insert_case1(node);
			_size++;
			_nil->parent = get_max_value_node();
			return ft::make_pair(node, true);
		}

		node_type* find(value_type val) const {
			node_type* res = _root;
			if (_size == 0)
				return ft_nullptr;
			while (res != ft_nullptr && val != *res->value) {
				if (_comp(val, *res->value))
					res = res->left_child;
				else
					res = res->right_child;
			}
			return res;
		}

	private :
		node_type* get_grandparent(node_type* node) const {
			if (node != ft_nullptr && node->parent != ft_nullptr)
				return node->parent->parent;
			else
				return ft_nullptr;
		}

		node_type* get_uncle(node_type* node) const {
			node_type* grand = get_grandparent(node);
			if (grand == ft_nullptr)
				return ft_nullptr;
			if (grand->left_child == node->parent)
				return grand->right_child;
			else if (grand->right_child == node->parent)
				return grand->left_child;
		}

		node_type* make_nil() {
			node_type* res = _node_alloc.allocate(1);
			_node_alloc.construct(res, node_type());
			res->color = BLACK;
			res->left_child = res;
			res->right_child = res;
			res->parent = res;
			res->value = ft_nullptr;
			return res;
		}

		node_type* make_node(const value_type& val) {
			node_type* res = _node_alloc.allocate(1);
			_node_alloc.construct(res, node_type(val));
			return res;
		}

		void copy(node_type* node) {
			if (node->value == ft_nullptr)
				return;
			insert(*node->value);
			if (node->left_child->value != ft_nullptr)
				copy(node->left_child);
			if (node->right_child->value != ft_nullptr)
				copy(node->right_child);
		}

		node_type* check_hint(value_type val, node_type* hint) {
			if (_comp(*hint->value, *_root->value) && _comp(val, *hint->value))
				return hint;
			else if (_comp(*hint->value, *_root->value) && _comp(*hint->value, val))
				return _root;
			else if (_comp(*_root->value, *hint->value) && _comp(val, *hint->value))
				return _root;
			else if (_comp(*_root->value, *hint->value) && _comp(*hint->value, val))
				return hint;
		}

		ft::pair<node_type*, bool> get_position(node_type* position, node_type* node) {
			while (position->value != ft_nullptr) {
				if (_comp(*node->value, *position->value)) {
					if (position->left_child->value == ft_nullptr) {
						position->left_child = node;
						node->parent = position;
						node->left_child = _nil;
						node->right_child = _nil;
						node->color = RED;
						break;
					}
					else
						position = position->left_child;
				}
				else if (_comp(*position->value, *node->value) {
					if (position->right_child->value == ft_nullptr) {
						position->right_child = node;
						node->parent = position;
						node->left_child = _nil;
						node->right_child = _nil;
						node->color = RED;
						break;
					}
					else
						position = position->right_child;
				}
				else
					return ft::make_pair(position, false);
			}
			return ft::make_pair(position, true);
		}

		void insert_case1(node_type* node) {
			// new_node is not root node
			if (node->parent != ft_nullptr)
				insert_case2(position, node);
		}

		void insert_case2(node_type* node) {
			// If new_node is RED, there is a problem.
			if (node->parent->color == RED)
				insert_case3(position, node);
		}

		void insert_case3(node_type* node) {
			// If new_node's parent and uncle is all RED,
			node_type* uncle = get_uncle(node);
			node_type* grand;
			if (uncle->value != ft_nullptr && uncle->color == RED) {
				node->parent->color = BLACK;
				uncle->color = BLACK;
				grand = get_grandparent(node);
				grand->color = RED;
				insert_case1(grand);
			}
			else
				insert_case4(position, node);
		}

		void insert_case4(node_type* node) {
			// If new_node's parent is RED and uncle is BLACK,
			node_type* grand = get_grandparent(node);
			// new_node is parent's right_child and parent is grand's left_child,
			if (node == node->parent->right_child && node->parent == grand->left_child) {
				rotate_left(node->parent);
				node = node->left_child;
			} // new_node is parent's left_child and parent is grand's right_child,
			else if (node = node->parent->left_child && node->parent == grand->right_child) {
				rotate_right(node->parent);
				node = node->right_child;
			}
			insert_case5(node);
		}

		void insert_case5(node_type* node) {
			node_type* grand = get_grandparent(node);
			node->parent->color = BLACK;
			grand->color = RED;
			if (node == node->parent->left_child)
				rotate_right(grand);
			else
				rotate_left(grand);
		}

		void rotate_left(node_type* node) {
			node_type* child = node->right_child;
			node_type* parent = node->parent;
			if (child->left_child->value != ft_nullptr)
				child->left_child->parent = node;
			node->right_child = child->left_child;
			node->parent = child;
			child->left_child = node;
			child->parent = parent;
			if (parent->value != ft_nullptr) {
				if (parent->left_child == node)
					parent->left_child = child;
				else
					parent->right_child = child;
			}
		}

		void rotate_right(node_type* node) {
			node_type* child = node->left_child;
			node_type* parent = node->parent;
			if (child->right_child->value != ft_nullptr)
				child->right_child->parent = node;
			node->left_child = child->right_child;
			node->parent = child;
			child->right_child = node;
			child->parent = parent;
			if (parent->value != ft_nullptr) {
				if (parent->right_child == node)
					parent->right_child = child;
				else
					parent->left_child = child;
			}
		}

		node_type* get_max_value_node() const {
			node_type* tmp = _root;
			while (tmp->right_child->value != ft_nullptr)
				tmp = tmp->right_child;
			return tmp;
		}

		/**
		 * @brief Member variables
		 */
		node_type*					_root;
		node_type*					_nil;
		size_type						_size;
		value_comp					_comp;
		node_allocator_type	_node_alloc;
	};
} // namespace ft


#endif
