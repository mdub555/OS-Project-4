# Project 4

A simulation of a trival OS memory manager.


Do file IO in main, make a simulation with a better constructor.
In simulation
For all addresses, do memory access
 inc mem accesses
 if not valid, segfault and exit
 get page table
 if page present
  update page table
 if not present, do fage fault
  if room
   give free frame
  else
   replace based on policy
 update page table and frame
