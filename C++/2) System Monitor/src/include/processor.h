#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <unistd.h>
#include "linux_parser.h"

using std::string;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  double lastIdleJiffes_;
  double lastTotalJiffes_;
};

#endif