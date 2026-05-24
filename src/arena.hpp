#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include <unordered_map>

struct page_hole {
  void *ptr;
  size_t size;
};

typedef std::vector<page_hole> FreeList;

class Page {
private:
  int32_t free_memory_;
  int32_t largest_free_block_;
  const char *data;
  size_t page_size;
  std::unordered_map<void*, int32_t> alloc_lists[7]; // 7 allocation lists for each 16^x up to 16^x==256M
                           // //used only for freeing
  FreeList free_lists[7];  // 7 free lists for each 16^x up to 16^x==256M
public:
  Page() = default;
  Page(int32_t size);

  void* alloc(int32_t size);
  void free(void* ptr);
};

class Arena {
  int32_t free_memory_;
  int32_t largest_free_block_;
  std::vector<Page> pages;
  std::vector<void *> big_data; // blobs larger than 128M
  FreeList free_lists[3]; // 3 free lists for each 16^x from 16^x>128M up to
                          // 16^x==64Gb
};
