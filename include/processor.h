#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <valarray>

#include "linux_parser.h"

class Processor {
 public:
  float Utilization();

 private:
  std::valarray<long> cpu_state_{LinuxParser::szCPUStates_};
};

#endif
