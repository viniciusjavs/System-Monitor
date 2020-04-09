#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include <string>

#include "process.h"
#include "processor.h"

class System {
 public:
  System();
  Processor& Cpu();
  std::set<Process>& Processes();
  float MemoryUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcesses();
  std::string Kernel() const;
  std::string OperatingSystem() const;

 private:
  Processor cpu_{};
  std::set<Process> processes_{};
  const std::string os_;
  const std::string kernel_;
};

#endif
