#include <arena.hpp>

static const size_t free_list_index_based_on_size(size_t size) {
  if (size < 16)
    return 0;
  if (size < 256)
    return 1;
  if (size < 256 * 16)
    return 2;
  if (size < 256 * 256)
    return 3;
  if (size < 256 * 256 * 16)
    return 4;
  if (size < 256 * 256 * 256)
    return 5;
  if (size < 256 * 256 * 256 * 16)
    return 6;
  if (size < (size_t)256 * 256 * 256 * 256)
    return 7;
  if (size < (size_t)256 * 256 * 256 * 256 * 16)
    return 8;
  return 9;
}

Page::Page(int32_t size) {
  free_memory_ = size;
  data = new char[size];
  page_size = size;
  free_lists[free_list_index_based_on_size(size)].push_back(
      {(void *)data, (size_t)size});
  largest_free_block_ = size;
}
