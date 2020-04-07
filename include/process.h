#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <valarray>

#include "linux_parser.h"

/*
  Basic class for Process representation
  It contains relevant attributes as shown below
*/

class Process {
 public:
  Process(int pid);
  int Pid() const;
  std::string User();
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();
  std::string Ram();                       // TODO: See src/process.cpp
  long UpTime();
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

 private:
  int pid_;
  std::valarray<long> cpu_state_{LinuxParser::ActiveJiffies(pid_), UpTime()};
};

#endif
