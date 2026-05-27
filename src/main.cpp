#include <arena.hpp>
#include <RedBlackTree_packed.hpp>

int main() {
  RedBlackTree<int, int> tree;
  tree.insert(1, 2);
  tree.insert(1, 2);
  tree.insert(1, 2);
  tree.insert(2, 2);
  tree.insert(3, 2);
}
