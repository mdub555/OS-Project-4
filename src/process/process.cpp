/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"

using namespace std;


Process* Process::read_from_input(std::istream& in) {
  // initialize all of the pages and get the total size
  vector<Page*> pages;
  Page* page;
  size_t total_size = 0;
  while ((page = Page::read_from_input(in))) {
    pages.push_back(page);
    total_size += page->size();
  }
  return new Process(total_size, pages);
}


size_t Process::size() const {
  return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  return index < pages.size();
}


size_t Process::get_rss() const {
  return page_table.get_present_page_count();
}


double Process::get_fault_percent() const {
  if (memory_accesses == 0) return 0.0;
  return (double) page_faults / memory_accesses * 100.0;
}
