/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"
#include <bitset>

using namespace std;


string PhysicalAddress::to_string() const {
  // there is a library that already does this quite well, so I'll use that instead
  return bitset<FRAME_BITS>(frame).to_string() + bitset<OFFSET_BITS>(offset).to_string();
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
  // this output matched the test case exactly
  out << address.to_string()
      << " [frame: " << address.frame
      << "; offset: " << address.offset
      << "]";
  return out;
}
