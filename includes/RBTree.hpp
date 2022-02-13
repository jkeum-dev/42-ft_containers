#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <stdexcept>
#include "MapIterator.hpp"
#include "printTree.hpp"
#include <iostream>

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

		void copy(node_type* node) {
			if (node->value == ft_nullptr)
				return;
			insert(*node->value);
			if (node->left_child->value != ft_nullptr)
				copy(node->left_child);
			if (node->right_child->value != ft_nullptr)
				copy(node->right_child);
		}

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
			insert_case1(new_node);
			_size++;
			_nil->parent = get_max_value_node();
			return ft::make_pair(new_node, true);
		}

		// Find the maximum in the left subtree or the minimum in the right subtree.
		// Then, move the value to the node to be deleted.
		size_type erase(node_type* node) {

			// 삭제할 노드 M을 찾아야 함.(node의 왼쪽 서브트리에서 최댓값 / 오른쪽 서브트리에서 최솟값)
			// node와 M을 바꾸고 M을 리턴받음.
			node = replace_erase_node(node);

			node_type* child;
			if (node->right_child->value == ft_nullptr)
				child = node->left_child;
			else
				child = node->right_child;
			// 1) M이 RED인 경우, 무조건 그 자식 노드들은 nil이었을 것이다(BLACK). M을 nil로 바꾸면 됨.
			replace_node(node, child);
			if (node->color == BLACK) {
				// 2) M이 BLACK이고 C가 RED인 경우, M을 C로 바꾸고 색을 BLACK으로 바꾼다.
				if (child->color == RED)
					child->color = BLACK;
				else
					delete_case1(child);
				// 3) M과 C가 모두 BLACK인 경우, C는 무조건 nil이었을 것이다. 
			}
			
			return 1;
		}

		void clear(node_type* node = ft_nullptr) {
			if (node == ft_nullptr)
				node = _root;
			if (node->left_child->value != ft_nullptr) {
				clear(node->left_child);
				node->left_child = _nil;
			}
			if (node->right_child->value != ft_nullptr) {
				clear(node->right_child);
				node->right_child = _nil;
			}
			// delete
			if (node->value != ft_nullptr) {
				if (node == _root)
					_root = _nil;
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
				_size--;
			}
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
			else
				return grand->left_child;
		}

		node_type* get_sibling(node_type* node) const {
			if (node == node->parent->left_child)
				return node->parent->right_child;
			else
				return node->parent->left_child;
		}

		node_type* get_max_value_node() const {
			node_type* tmp = _root;
			while (tmp->right_child->value != ft_nullptr)
				tmp = tmp->right_child;
			return tmp;
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

		node_type* check_hint(value_type val, node_type* hint) {
			if (_comp(*hint->value, *_root->value) && _comp(val, *hint->value))
				return hint;
			else if (_comp(*hint->value, *_root->value) && _comp(*hint->value, val))
				return _root;
			else if (_comp(*_root->value, *hint->value) && _comp(val, *hint->value))
				return _root;
			else if (_comp(*_root->value, *hint->value) && _comp(*hint->value, val))
				return hint;
			else
				return _root;
		}

		ft::pair<node_type*, bool> get_position(node_type* position, node_type* node) {
			while (position->value != ft_nullptr) {
				// std::cout << "here : " << position->value->first << std::endl;
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
				else if (_comp(*position->value, *node->value)) {
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
			if (node->parent->value != ft_nullptr)
				insert_case2(node);
			else
				node->color = BLACK;
		}

		void insert_case2(node_type* node) {
			// If new_node is RED, there is a problem.
			if (node->parent->color == RED)
				insert_case3(node);
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
				insert_case4(node);
		}

		void insert_case4(node_type* node) {
			// If new_node's parent is RED and uncle is BLACK,
			node_type* grand = get_grandparent(node);
			// new_node is parent's right_child and parent is grand's left_child,
			if (node == node->parent->right_child && node->parent == grand->left_child) {
				rotate_left(node->parent);
				node = node->left_child;
			} // new_node is parent's left_child and parent is grand's right_child,
			else if (node == node->parent->left_child && node->parent == grand->right_child) {
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
			else
				_root = child;
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
			else
				_root = child;
		}

		node_type* replace_erase_node(node_type* node) {
			// node의 왼쪽 서브트리에서 최댓값 / 오른쪽 서브트리에서 최솟값
			node_type* result;
			if (node->left_child->value != ft_nullptr) {
				result = node->left_child;
				while (result->right_child->value != ft_nullptr) {
					if (result->right_child->value != ft_nullptr)
						result = result->right_child;
				}
			}
			else {
				result = node->right_child;
				while (result->left_child->value != ft_nullptr) {
					if (result->left_child->value != ft_nullptr)
						result = result->left_child;
				}
			}
			node->value = result->value;
			return result;
		}

		void replace_node(node_type* node, node_type* child) {
			// The case where the parent of node becomes ft_nullptr
			// can be handled in advance so that it does not come into delete_case.
			child->parent = node->parent;
			if (node->parent->left_child == node)
				node->parent->left_child = child;
			else if (node->parent->right_child == node)
				node->parent->right_child = child;
		}

		void delete_case1(node_type* node) {
			if (node->parent->value != ft_nullptr)
				delete_case2(node);
		}

		void delete_case2(node_type* node) {
			node_type* sibling = get_sibling(node);
			if (sibling->color == RED) {
				node->parent->color = RED;
				sibling->color = BLACK;
				if (node == node->parent->left_child)
					rotate_left(node->parent);
				else
					rotate_left(node->parent);
			}
			delete_case3(node);
		}

		void delete_case3(node_type* node) {
			node_type* sibling = get_sibling(node);
			if (node->parent->color == BLACK && sibling->color == BLACK &&
					sibling->left_child->color == BLACK && sibling->right_child->color == BLACK) {
				sibling->color = RED;
				delete_case1(node->parent);
			}
			else
				delete_case4(node);
		}

		void delete_case4(node_type* node) {
			node_type* sibling = get_sibling(node);
			if (node->parent->color == RED && sibling->color == BLACK &&
					sibling->left_child->color == BLACK && sibling->right_child->color == BLACK) {
				sibling->color = RED;
				node->parent->color = BLACK;
			}
			else
				delete_case5(node);
		}

		void delete_case5(node_type* node) {
			node_type* sibling = get_sibling(node);
			if (sibling->color == BLACK) {
				if (node == node->parent->left_child &&
						sibling->right_child->color == BLACK && sibling->left_child->color == RED) {
					sibling->color = RED;
					sibling->left_child->color = BLACK;
					rotate_right(sibling);
				}
				else if (node == node->parent->right_child &&
								sibling->left_child->color == BLACK && sibling->right_child->color == RED) {
					sibling->color = RED;
					sibling->right_child->color = BLACK;
					rotate_left(sibling);
				}
			}
			delete_case6(node);
		}

		void delete_case6(node_type* node) {
			node_type* sibling = get_sibling(node);
			sibling->color = node->parent->color;
			node->parent->color = BLACK;
			if (node == node->parent->left_child) {
				sibling->right_child->color = BLACK;
				rotate_left(node->parent);
			}
			else {
				sibling->left_child->color = BLACK;
				rotate_right(node->parent);
			}
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
