//
//  RedBlackTree.h
//  red-black-tree
//
//  Created by Yassaman Ommi on 2018-11-27.
//

#ifndef RedBlackTree_h
#define RedBlackTree_h

#include <vector>
#endif /* RedBlackTree_h */

#include <iostream>

enum Color { RED, BLACK };

template <typename Key, typename Value> struct Node {
  Color color;
  int32_t left;
  int32_t right;
  int32_t parent;
  int32_t index;
  Key data;
  std::vector<Value> value;

  explicit Node(int val)
      : data(val), color(RED), left(-1), right(-1), parent(-1) {}
};

template <typename Key, typename Value> class RedBlackTree {
  using Node = Node<Key, Value>;

private:
  int32_t root = -1;
  std::vector<Node> nodes{};

  //  left rotation
  void leftRotate(Node *x) {
    if (x == nullptr)
      return;

    if (x->right == nullptr)
      return;

    Node *y = &nodes[x->right];
    x->right = y->left;
    if (y->left != -1)
      &nodes[y->left]->parent = x;
    y->parent = x->parent;
    if (x->parent == -1)
      root = y->index;
    else if (x->index == &nodes[x->parent]->left)
      &nodes[x->parent]->left = y->index;
    else
      &nodes[x->parent]->right = y->index;
    y->left = x->index;
    x->parent = y->index;
  }

  //  right rotation
  void rightRotate(Node *y) {
    if (y == nullptr)
      return;

    if (y->left == nullptr)
      return;

    Node *x = &nodes[y->left];
    y->left = x->right;
    if (x->right != -1)
      &nodes[x->right]->parent = y->index;
    x->parent = y->parent;
    if (y->parent == -1)
      root = x->index;
    else if (y->index == &nodes[y->parent]->left)
      &nodes[y->parent]->left = x->index;
    else
      &nodes[y->parent]->right = x->index;
    x->right = y->index;
    y->parent = x->index;
  }

  // fix violations after inserting a node
  void fixInsert(Node *z) {
    while (z->index != root && &nodes[z->parent]->color == RED) {
      if (z->parent == &nodes[&nodes[z->parent]->parent]->left) {
        Node *y = (nodes.data() + &nodes[&nodes[z->parent]->parent]->right);
        if (y != nullptr && y->color == RED) {
          &nodes[z->parent]->color = BLACK;
          y->color = BLACK;
          &nodes[&nodes[z->parent]->parent]->color = RED;
          z = &nodes[&nodes[z->parent]->parent];
        } else {
          if (z->index == &nodes[z->parent]->right) {
            z = &nodes[z->parent];
            leftRotate(z);
          }
          &nodes[z->parent]->color = BLACK;
          &nodes[&nodes[z->parent]->parent]->color = RED;
          rightRotate(&nodes[&nodes[z->parent]->parent]);
        }
      } else {
        Node *y = (nodes.data() + &nodes[&nodes[z->parent]->parent]->left);
        if (y != nullptr && y->color == RED) {
          &nodes[z->parent]->color = BLACK;
          y->color = BLACK;
          &nodes[&nodes[z->parent]->parent]->color = RED;
          z = &nodes[&nodes[z->parent]->parent];
        } else {
          if (z->index == &nodes[z->parent]->left) {
            z = z->parent;
            rightRotate(z);
          }
          &nodes[z->parent]->color = BLACK;
          &nodes[&nodes[z->parent]->parent]->color = RED;
          leftRotate(&nodes[&nodes[z->parent]->parent]);
        }
      }
    }
    &nodes[root]->color = BLACK;
  }

  // Transplant function used in deletion
  void transplant(Node *u, Node *v) {
    if (u->parent == -1)
      root = v;
    else if (u->index == &nodes[u->parent]->left)
      &nodes[u->parent]->left = v->index;
    else
      &nodes[u->parent]->right = v->index;
    if (v != nullptr)
      v->parent = u->parent;
  }

  //    delete a node
  void deleteNode(Node *z) {
    if (z == nullptr)
      return;

    Node *y = z;
    Node *x = nullptr;
    Color y_original_color = y->color;

    if (z->left == -1) {
      x = &nodes[z->right];
      transplant(z, &nodes[z->right]);
    } else if (z->right == nullptr) {
      x = &nodes[z->left];
      transplant(z, &nodes[z->left]);
    } else {
      y = minimum(&nodes[z->right]);
      y_original_color = y->color;
      x = &nodes[y->right];

      if (y->parent == z->index) {
        if (x != nullptr)
          x->parent =
              y->index; // Check if x is not nullptr before assigning parent
      } else {
        if (x != nullptr)
          x->parent = y->parent; // Check if x and y->parent are not nullptr
                                 // before assigning parent
        transplant(y, &nodes[y->right]);
        if (y->right != -1)
          &nodes[y->right]->parent =
              y->index; // Check if y->right is not nullptr before assigning
                        // parent
        y->right = z->right;
        if (y->right != -1)
          &nodes[y->right]->parent =
              y->index; // Check if y->right is not nullptr before assigning
                        // parent
      }
      transplant(z, y);
      y->left = z->left;
      if (y->left != -1)
        &nodes[y->left]->parent =
            y->index; // Check if y->left is not nullptr before assigning parent
      y->color = z->color;
    }

    if (y_original_color == BLACK && x != nullptr) // Check if x is not nullptr
      fixDelete(x);

    delete z; // Free memory allocated for the deleted node
  }

  // Function to fix violations after deleting a node
  void fixDelete(Node *x) {
    while (x->index != root && x != nullptr && x->color == BLACK) {
      if (x->index == &nodes[x->parent]->left) {
        Node *w = &nodes[&nodes[x->parent]->right];
        if (w->color == RED) {
          w->color = BLACK;
          &nodes[x->parent]->color = RED;
          leftRotate(&nodes[x->parent]);
          w = &nodes[&nodes[x->parent]->right];
        }
        if ((w->left == -1 || &nodes[w->left]->color == BLACK) &&
            (w->right == -1 || &nodes[w->right]->color == BLACK)) {
          w->color = RED;
          x = &nodes[x->parent];
        } else {
          if (w->right == -1 || &nodes[w->right]->color == BLACK) {
            if (w->left != -1)
              &nodes[w->left]->color = BLACK;
            w->color = RED;
            rightRotate(w);
            w = &nodes[&nodes[x->parent]->right];
          }
          w->color = &nodes[x->parent]->color;
          &nodes[x->parent]->color = BLACK;
          if (w->right != -1)
            &nodes[w->right]->color = BLACK;
          leftRotate(&nodes[x->parent]);
          x = &nodes[root];
        }
      } else {
        Node *w = &nodes[&nodes[x->parent]->left];
        if (w->color == RED) {
          w->color = BLACK;
          &nodes[x->parent]->color = RED;
          rightRotate(&nodes[x->parent]);
          w = &nodes[&nodes[x->parent]->left];
        }
        if ((w->right == -1 || &nodes[w->right]->color == BLACK) &&
            (w->left == -1 || &nodes[w->left]->color == BLACK)) {
          w->color = RED;
          x = &nodes[x->parent];
        } else {
          if (w->left == -1 || &nodes[w->left]->color == BLACK) {
            if (w->right != -1)
              &nodes[w->right]->color = BLACK;
            w->color = RED;
            leftRotate(w);
            w = &nodes[&nodes[x->parent]->left];
          }
          w->color = &nodes[x->parent]->color;
          &nodes[x->parent]->color = BLACK;
          if (w->left != -1)
            w->left->color = BLACK;
          rightRotate(&nodes[x->parent]);
          x = &nodes[root];
        }
      }
    }
    if (x != nullptr)
      x->color = BLACK;
  }

  // find the minimum node in a subtree
  Node *minimum(Node *node) {
    while (node->left != -1)
      node = &nodes[node->left];
    return node;
  }

  // print the tree structure (in-order traversal)
  void printHelper(Node *root, int space) {
    constexpr int COUNT = 5;
    if (root == -1)
      return;
    space += COUNT;
    printHelper(&nodes[root->right], space);
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
      std::cout << " ";
    std::cout << &nodes[root]->data << "(" << ((&nodes[root]->color == RED) ? "RED" : "BLACK")
              << ")" << std::endl;
    printHelper(&nodes[root->left], space);
  }

public:
  RedBlackTree() : root(-1) {}

  // insert a node
  void insert(int val) {
    Node *newNode = new Node(val);
    Node *y = nullptr;
    Node *x = root;

    while (x != nullptr) {
      y = x;
      if (newNode->data < x->data)
        x = &nodes[x->left];
      else if (newNode->data > x->data)
        x = &nodes[x->right];
      else {
        x->value.push_back(val);
        return;
      }
    }

    newNode->parent = y->index;
    if (y == nullptr)
      root = newNode->index;
    else if (newNode->data < y->data)
      y->left = newNode->index;
    else
      y->right = newNode->index;

    fixInsert(newNode);
  }

  // delete a node by value
  void remove(int val) {
    Node *z = root;
    while (z != nullptr) {
      if (val < z->data)
        z = &nodes[z->left];
      else if (val > z->data)
        z = &nodes[z->right];
      else {
        if (z->value.size() > 1) {
          z->value.pop_back();
          return;
        }
        deleteNode(z);
        return;
      }
    }
    std::cout << "Node with value " << val << " not found in the tree."
              << std::endl;
  }

  // print the tree structure
  void printTree() { printHelper(root, 0); }
};
