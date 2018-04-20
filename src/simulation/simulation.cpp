/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include <fstream>
#include <iostream>
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
  // TODO: implement me
  ifstream in(filename);
  if (in.is_open()) read_processes(in);

  // output process size in bytes (for deliverable 1)
  cout << "Process and size" << endl;
  for (pair<int, Process*> entry : processes) {
    cout << entry.first << " " << entry.second->size() << endl;
  }

  // output all the virtual addresses in the file (for deliverable 1)
  cout << endl << "Virtual addresses:" << endl;
  int pid;
  string virt_addr;
  while (in >> pid >> virt_addr) {
    cout << pid << " " << virt_addr << endl;
  }

  in.close();
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
  // TODO: implement me
  return 0;
}


void Simulation::handle_page_fault(Process* process, size_t page) {
  // TODO: implement me
}
