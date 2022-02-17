#if !defined(PRINTTREE_HPP)
#define PRINTTREE_HPP

#include <iostream>

#include "RBTree.hpp"

#define C_RED "\033[0;31m"
#define C_RESET "\e[0m"

namespace ft {
template < typename T >
void printMap(RBTreeNode< T >* node, int depth) {
  if (depth == 0) {
    std::cout << "// SHOW TREE //" << std::endl;
  }
  int tmp_depth = depth;
  if (node->value == ft_nullptr) {
    while (tmp_depth--) {
      std::cout << "     ";
    }
    std::cout << "nil" << std::endl;
    return;
  }
  while (tmp_depth--) {
    std::cout << "     ";
  }
  std::cout << (node->color ? C_RESET : C_RED)
            << (node->parent->value == ft_nullptr ? "Root" : (node->parent->left_child == node ? "L" : "R"))
            << " - key: " << node->value->first << C_RESET << std::endl;
  if (node->left_child->value != ft_nullptr) {
    // std::cout << "left?" << std::endl;
    printMap(node->left_child, depth + 1);
  }
  if (node->right_child->value != ft_nullptr) {
    printMap(node->right_child, depth + 1);
  }
    // std::cout << "right?" << std::endl;
  return;
}
}  // namespace ft

#endif  // PRINTTREE_HPP