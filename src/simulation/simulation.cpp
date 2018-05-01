/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include <fstream>
#include <iostream>
#include <cassert>
#include "simulation/simulation.h"

using namespace std;


bool Simulation::read_processes(std::istream& in) {
  // get number of processes
  int num_processes;
  in >> num_processes;

  // read in data for all processes
  int pid;
  std::string proc_file;
  for (int i = 0; i < num_processes; i++) {
    // get pid and filename
    in >> pid >> proc_file;
    // turn filename into an input stream
    ifstream input(proc_file);
    // add the process to the processes map
    processes.insert(pair<int, Process*>(pid, Process::read_from_input(input)));
    input.close();
  }

  return true;
}


void Simulation::run() {
  ifstream in(filename);
  if (in.is_open()) read_processes(in);

  // output all the virtual addresses in the file (for deliverable 1)
  int pid;
  string virt_addr;
  while (in >> pid >> virt_addr) {
    VirtualAddress temp = VirtualAddress::from_string(pid, virt_addr);
    virt_addrs.push_back(temp);
  }

  in.close();

  char output[virt_addrs.size()];
  // do all the memory accesses
  for (size_t i = 0; i < virt_addrs.size(); i++) {
    output[i] = perform_memory_access(virt_addrs[i]);
  }
  cout << output << endl;
  cout << endl
       << "DONE!" << endl << endl;

  // output process information
  size_t accesses = 0, faults = 0;
  for (std::pair<int, Process*> entry : processes) {
    Process* p = entry.second;
    printf("Process %3d:  ACCESSES: %-6lu FAULTS: %-6lu FAULT RATE: %-8.2f RSS: %-6lu\n",
    entry.first, p->memory_accesses, p->page_faults, p->get_fault_percent(), p->get_rss());
    accesses += p->memory_accesses;
    faults += p->page_faults;
  }

  // output overall statistics
  cout << endl;
  printf("Total memory accesses: %15lu\n", accesses);
  printf("Total page faults:     %15lu\n", faults);
  printf("Free frames remaining: %15lu\n", NUM_FRAMES - frames.size());
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
  cout << address << endl;
  // get the process for this virtual address
  Process* p = processes[address.process_id];
  p->memory_accesses++;

  // check if the address is valid and crash if it's not
  if (!p->is_valid_page(address.page)) {
    cerr << "[SEGFAULT] Invalid memory access " << address << endl;
    exit(EXIT_FAILURE);
  }

  // handle a page fault if the page is not present in main memory
  if (!p->page_table.rows[address.page].present) {
    cout << "  -> PAGE FAULT" << endl;
    p->page_faults++;
    handle_page_fault(p, address.page);
  } else {
    cout << "  -> IN MEMORY" << endl;
  }

  // update the access time
  p->page_table.rows[address.page].last_accessed_at = virtual_time++;

  // create the physical address
  size_t frame = p->page_table.rows[address.page].frame;
  PhysicalAddress phys_addr(frame, address.offset);
  cout << "  -> physical address " << phys_addr << endl;
  printf("  -> RSS: %-6lu\n\n", p->page_table.get_present_page_count());

  // return the data in the frame
  return p->pages[frames[frame].page_number]->get_byte_at_offset(phys_addr.offset);
}


void Simulation::handle_page_fault(Process* process, size_t page) {
  // attempt to load the page into memory
  int res_set = process->page_table.get_present_page_count();
  assert(res_set <= max_frames);
  assert(frames.size() <= NUM_FRAMES);

  Frame frame;
  frame.set_page(process, page);

  if (res_set == max_frames || frames.size() == NUM_FRAMES) {
    // page table is full or no full frames, replace a row
    size_t row_to_replace;
    switch(strategy) {
    case ReplacementStrategy::LRU:
      row_to_replace = process->page_table.get_least_recently_used_page();
      break;
    case ReplacementStrategy::FIFO:
      row_to_replace = process->page_table.get_oldest_page();
      break;
    }
    process->page_table.rows[row_to_replace].present = false;

    // get the frame to replace
    int index = 0;
    for (size_t i = 0; i < frames.size(); i++) {
      if (frames[i].process == process && frames[i].page_number == row_to_replace) {
        index = i;
        break;
      }
    }
    frames[index] = frame;
    process->page_table.rows[page].frame = index;
  } else {
    frames.push_back(frame);
    process->page_table.rows[page].frame = frames.size()-1;
  }

  // load into memory, set present, pass page to next available frame, remove it from free
  // availible frame vector
  process->page_table.rows[page].present = true;
  process->page_table.rows[page].loaded_at = virtual_time;
}
