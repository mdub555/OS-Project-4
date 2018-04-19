/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <iostream>
#include <getopt.h>

using namespace std;


void print_usage() {
  cout <<
      "Usage: mem-sim [options] filename\n"
      "\n"
      "Options:\n"
      "  -v, --verbose\n"
      "      Output information about every memory access.\n"
      "\n"
      "  -s, --strategy (FIFO | LRU)\n"
      "      The replacement strategy to use. One of FIFO or LRU.\n"
      "\n"
      "  -f, --max-frames <positive integer>\n"
      "      The maximum number of frames a process may be allocated.\n"
      "\n"
      "  -h --help\n"
      "      Display a help message about these flags and exit\n"
      "\n";
}


bool parse_flags(int argc, char** argv, FlagOptions& flags) {
  static struct option flag_options[] = {
    {"verbose",    no_argument,       0, 'v'},
    {"strategy",   required_argument, 0, 's'},
    {"max-frames", required_argument, 0, 'f'},
    {"help",       no_argument,       0, 'h'},
    {0, 0, 0, 0}
  };

  int option_index;
  char flag_char;

  while (true) {
    flag_char = getopt_long(argc, argv, "-vs:f:h", flag_options, &option_index);

    if (flag_char == -1) break;

    switch (flag_char) {
    case 'v':
      flags.verbose = true;
      break;

    case 's': {
      string option(optarg);
      if (option == "LRU") {
        flags.strategy = ReplacementStrategy::LRU;
      } else if (option == "FIFO") {
        flags.strategy = ReplacementStrategy::FIFO;
      } else {
        print_usage();
        return false;
      }
      break;
    }

    case 'f': {
      if (!isdigit(optarg[0])) {
        print_usage();
        return false;
      }
      int frames = atoi(optarg);
      if (frames <= 0) {
        print_usage();
        return false;
      }
      flags.max_frames = frames;
      break;
    }

    case 'h':
      print_usage();
      exit(EXIT_SUCCESS);
      break;

    case 1:
      flags.filename = optarg;
      break;

    default:
      print_usage();
      return false;
      break;
    }
  }

  if (flags.filename == "") {
    print_usage();
    return false;
  }

  return true;
}
