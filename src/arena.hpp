#pragma once
#include <RedBlackTree.h>
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <vector>

// struct page_hole {
//   void *ptr;
//   size_t size;
// };

typedef RedBlackTree<size_t, void *> FreeList;

class Page {
private:
  int32_t free_memory = 0;
  const unsigned char *data;
  int32_t page_size = 0;
  Node<size_t, void *>* largest_free_block;
  std::unordered_map<void *, int32_t> alloc_list; // used only for freeing
  FreeList free_list;

public:
  Page() = default;
  Page(int32_t size);

  void *alloc(int32_t size);
  void free(void *ptr);
};

class Arena {
  int32_t free_memory;
  std::vector<Page> pages;
  std::vector<void *> big_data; // blobs larger than 128M
  FreeList free_list;           // blobs larger than 128M
};
