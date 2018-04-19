/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"
#include <bitset>

using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  // convert the string to a size_t
  size_t addr = stoi(address, nullptr, 2);
  // get the page from the addr size_t
  size_t page = (addr & PAGE_BITMASK) >> OFFSET_BITS;
  // get the offset from the addr size_t
  size_t offset = addr & OFFSET_BITMASK;
  return VirtualAddress(process_id, page, offset);
}


string VirtualAddress::to_string() const {
  // use the feature that does this for me
  return bitset<PAGE_BITS>(page).to_string() + bitset<OFFSET_BITS>(offset).to_string();
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  out << "PID " << address.process_id
      << " @ " << address.to_string()
      << " [page: " << address.page
      << "; offset: " << address.offset
      << "]";
  return out;
}
