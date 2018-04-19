/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  char c;
  vector<char> bytes;
  size_t i = 0;
  while (in.get(c) && i < PAGE_SIZE) {
    bytes.push_back(c);
    i++;
  }
  if (bytes.size() == 0) return nullptr;
  return new Page(bytes);
}


size_t Page::size() const {
  return bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
  return offset < size();
}


char Page::get_byte_at_offset(size_t offset) {
  if (is_valid_offset(offset)) return bytes[offset];
  return 0;
}
