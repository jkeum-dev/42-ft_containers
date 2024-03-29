#ifndef SETTREE_HPP
#define SETTREE_HPP

#include <stdexcept>
#include "SetIterator.hpp"

namespace ft
{
	/**
	 * @brief SetTree class
	 * set base - red black tree
	 * 
	 * @tparam T				value_type (pair of key and mapped_type)
	 * @tparam Compare	A binary predicate that takes two element keys as arguments and returns a bool.
	 * @tparam Alloc		Type of the allocator object used to define the storage allocation model.
	 */
	template < typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
	class SetTree {
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
		typedef typename ft::SetIterator<T, false>								iterator;
		typedef typename ft::SetIterator<T, true>									const_iterator;
		typedef typename Alloc::template rebind<node_type>::other node_allocator_type;

		/**
		 * @brief Member functions
		 */
		// Default constructor
		SetTree() : _root(ft_nullptr), _nil(ft_nullptr), _size(0),
							_comp(value_comp()), _node_alloc(node_allocator_type()) {
			_nil = make_nil();
			_root = _nil;
		}

		// Copy constructor
		SetTree(const SetTree& _copy) : _root(ft_nullptr), _nil(ft_nullptr), _size(0),
																	_comp(value_comp()), _node_alloc(node_allocator_type()) {
			_nil = make_nil();
			copy(_copy);
			_nil->parent = get_max_value_node();
		}

		// Destructor
		~SetTree() {
			clear();
			_node_alloc.destroy(_nil);
			_node_alloc.deallocate(_nil, 1);
		}

		// Assignment operator
		SetTree& operator=(const SetTree& x) { if (this != &x) copy(x); return *this; }

		void copy(const SetTree& x) {
			clear();
			copy(x._root);
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
		size_type max_size() const { return _node_alloc.max_size(); }

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

		size_type erase(node_type* node) {
			if (node->value == ft_nullptr)
				return 0;
			// node의 왼쪽 서브트리에서 최댓값 / 오른쪽 서브트리에서 최솟값을 찾음.
			// node와 M의 값을 바꾸고 M을 리턴받음.
			node_type* real = replace_erase_node(node);
			// 진짜 삭제할 노드는 M(real)이고, 그 자식 노드를 child라고 함.
			node_type* child;
			if (real->right_child->value == ft_nullptr)
				child = real->left_child;
			else
				child = real->right_child;
			// 1) M이 RED인 경우, 무조건 그 자식 노드들은 nil이었을 것이다(BLACK). M을 nil로 바꾸면 됨.
			replace_node(real, child);
			if (real->color == BLACK) {
				// 2) M이 BLACK이고 C가 RED인 경우, M을 C로 바꾸고 색을 BLACK으로 바꾼다.
				if (child->color == RED)
					child->color = BLACK;
				else
					delete_case1(child);
				// 3) M과 C가 모두 BLACK인 경우, C는 무조건 nil이었을 것이다. 
			}
			_size--;
			if (real->parent->value == ft_nullptr)
				_root = _nil;
			delete real;
			_nil->parent = get_max_value_node();
			return 1;
		}

		void swap(SetTree& x) {
			swap(_root, x._root);
			swap(_nil, x._nil);
			swap(_comp, x._comp);
			swap(_size, x._size);
			swap(_node_alloc, x._node_alloc);
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

		// Operations:
		node_type* find(value_type val) const {
			node_type* res = _root;
			if (_size == 0)
				return _nil;
			while (res->value != ft_nullptr && (_comp(val, *res->value) || _comp(*res->value, val))) {
				if (_comp(val, *res->value))
					res = res->left_child;
				else
					res = res->right_child;
			}
			return res;
		}

		node_type* lower_bound(const value_type& val) const {
			iterator it(get_begin());
			iterator ite(get_end());
			while (it != ite) {
				if (!_comp(*it, val))
					break;
				it++;
			}
			return it.base();
		}

		node_type* upper_bound(const value_type& val) const {
			iterator it(get_begin());
			iterator ite(get_end());
			while (it != ite) {
				if (_comp(val, *it))
					break;
				it++;
			}
			return it.base();
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
			// node의 left_child가 있으면, 왼쪽 서브트리에서 최댓값,
			// node의 left_child가 없으면, 오른쪽 서브트리에서 최솟값을 찾는다.
			// 찾은 값의 value를 node에 복사하고, 찾은 그 노드는 삭제해야 하므로 리턴한다.
			node_type* result;
			if (node->left_child->value != ft_nullptr) {
				result = node->left_child;
				while (result->right_child->value != ft_nullptr)
					result = result->right_child;
			}
			else if (node->right_child->value != ft_nullptr) {
				result = node->right_child;
				while (result->left_child->value != ft_nullptr)
					result = result->left_child;
			}
			else
				return node;

			node_type* tmp_parent = node->parent;
			node_type* tmp_left = node->left_child;
			node_type* tmp_right = node->right_child;
			RBColor tmp_color = node->color;

			// node의 left/right_child 설정
			node->left_child = result->left_child;
			if (result->left_child->value != ft_nullptr)
				result->left_child->parent = node;
			node->right_child = result->right_child; 
			if (result->right_child->value != ft_nullptr)
				result->right_child->parent = node;

			// result를 node->parent의 left/right_child로 설정
			if (tmp_parent->left_child == node)
				tmp_parent->left_child = result;
			else if (tmp_parent->right_child == node)
				tmp_parent->right_child = result;

			if (result == tmp_left) {
				// result의 형제를 result의 left/right_child로 연결
				tmp_right->parent = result;
				result->right_child = tmp_right;
				// node를 result의 left/right_child로 연결
				node->parent = result;
				result->left_child = node;
			}
			else if (result == tmp_right) {
				tmp_left->parent = result;
				result->left_child = tmp_left;
				node->parent = result;
				result->right_child = node;
			}
			else {
				// result와 node가 멀리 떨어진 경우
				tmp_left->parent = result;
				result->left_child = tmp_left;
				tmp_right->parent = result;
				result->right_child = tmp_right;
				node->parent = result->parent;
				result->parent->right_child = node;
			}

			// result의 parent 연결
			result->parent = tmp_parent;

			if (result->parent->value == ft_nullptr)
				_root = result;
			node->color = result->color;
			result->color = tmp_color;

			return node;
		}

		void replace_node(node_type* node, node_type* child) {
			// The case where the parent of node becomes ft_nullptr
			// can be handled in advance so that it does not come into delete_case.
			child->parent = node->parent;
			if (node->parent->left_child == node)
				node->parent->left_child = child;
			else// if (node->parent->right_child == node)
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
					rotate_right(node->parent);
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
			node_type* tmp = node->parent;
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
			node->parent = tmp;
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

		template <typename _T>
		void swap(_T& a, _T& b) {
			_T tmp(a);
			a = b;
			b = tmp;
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
