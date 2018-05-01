# Project 3 - CPU Scheduling Simulator

## Name
Mitchell Waibel

## Files
* `makefile` - used to build the program.
* `README.md` - this file.

* `inputs/`
  * `belady` - simulation input to see Belady's Anomaly.
  * `process_1` - data for process 1.
  * `process_2` - data for process 2.
  * `process_3` - data for process 3.
  * `sim_1` - the first example simulation.
  * `sim_2` - the second example simulation.

* `src/`
  * `flag_parser/` - functions to parse the command line arguments.
  * `frame/` - a class for a frame of memory.
  * `main.cpp` - the initializer for the simulation
  * `page/` - an individual page holding data.
  * `page_table/` - page table class used in each process.
  * `physical_address/` - a physical address class with frame and offset.
  * `process/` - a process chall to hold and access process data.
  * `simulation/` - the simulation which does all memory accesses.
  * `virtual_address/` - a virtual address class with page and offset.

## Features
This program does not include any additional features.

## Time Spent
| Deliverable     | Time    |
| --------------- | -------:|
| Pass Test Cases | 4 hours |
| Simulation      | 4 hours |
| _Total_         | 8 hours |

## Belady's Anomaly
Belady's Anomaly is a phenomemon where adding more frames to your process (which
gives it more memory) actually increases the number of page faults for a
specific page access pattern. This is quite unintuitive, and mainly occurs when
using the FIFO replacement algorithm. It occurs because increasing the number of
frames changes when each frame is removed from memory, which in very specific
memory access patterns can cause something to be removed right before it's used
when it would otherwise not have been removed.

In order to see this Anomoly:

3 frames and 9 page faults:

`./mem-sim -f 3 inputs/belady`

4 frames and 10 page faults:

`./mem-sim -f 4 inputs/belady`
