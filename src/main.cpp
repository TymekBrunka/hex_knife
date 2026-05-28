#include <arena.hpp>

int main() {
  RedBlackTree<int, int> tree;
  tree.insert(1, 2);
  tree.insert(1, 2);
  tree.insert(1, 2);
  tree.insert(2, 2);
  tree.insert(3, 2);
  tree.printTree();
}
