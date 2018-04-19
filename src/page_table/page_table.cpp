/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"

using namespace std;


size_t PageTable::get_present_page_count() const {
  size_t pages = 0;
  for (size_t i = 0; i < rows.size(); i++) {
    if (rows[i].present) pages++;
  }
  return pages;
}


size_t PageTable::get_oldest_page() const {
  // largest possible value (unsigned)
  size_t oldest_time = -1;
  size_t index = 0;
  for (size_t i = 0; i < rows.size(); i++) {
    if (rows[i].present && rows[i].loaded_at < oldest_time) {
      oldest_time = rows[i].loaded_at;
      index = i;
    }
  }
  return index;
}


size_t PageTable::get_least_recently_used_page() const {
  // largest possible value (unsigned)
  size_t oldest_time = -1;
  size_t index = 0;
  for (size_t i = 0; i < rows.size(); i++) {
    if (rows[i].present && rows[i].last_accessed_at < oldest_time) {
      oldest_time = rows[i].last_accessed_at;
      index = i;
    }
  }
  return index;
}
