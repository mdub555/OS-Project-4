/**
 * This file contains the definition of the Simulation class.
 *
 * You're free to modify this class however you see fit. Add new methods to help
 * keep your code modular.
 */

#pragma once
#include "process/process.h"
#include "virtual_address/virtual_address.h"
#include "physical_address/physical_address.h"
#include "flag_parser/flag_parser.h"
#include "frame/frame.h"
#include <cstdlib>
#include <map>


/**
 * Class responsible for running the memory simulation.
 */
class Simulation {
// PUBLIC CONSTANTS
public:

  /**
   * The maximum number of frames in the simulated system (512).
   */
  static const size_t NUM_FRAMES = 1 << 9;

// PUBLIC API METHODS
public:

  /**
   * Constructor
   */
  Simulation(FlagOptions flags) : filename(flags.filename),
                                  strategy(flags.strategy),
                                  verbose(flags.verbose),
                                  max_frames(flags.max_frames) {}

  /**
   * Runs the simulation.
   */
  void run();

// PRIVATE METHODS
private:
  /**
   * Performs a memory access for the given virtual address, translating it to
   * a physical address and loading the page into memory if needed. Returns the
   * byte at the given address.
   */
  char perform_memory_access(const VirtualAddress& address);

  /**
   * Handles a page fault, attempting to load the given page for the given
   * process into memory.
   */
  void handle_page_fault(Process* process, size_t page);

  /**
   * Reads in the processes from the file given the file format and adds the process to the map of
   * processes.
   */
  bool read_processes(std::istream& in);

// INSTANCE VARIABLES
private:
  /**
   * The filename of the main input file
   */
  std::string filename;

  /**
   * The strategy given via the command line arguments. LRU or FIFO.
   */
  ReplacementStrategy strategy;

  /**
   * Whether or not the output should be verbose
   */
  bool verbose;

  /**
   * The number of frames given to a program. Default: 10
   */
  int max_frames;

  /**
   * A map of processes to hold all the information in each of the process files.
   */
  std::map<int, Process*> processes;
  std::vector<VirtualAddress> virt_addrs;
  std::vector<Frame> frames;
  int virtual_time = 0;
};
