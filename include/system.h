#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  System();
  Processor& Cpu();
  std::vector<Process>& Processes();
  float MemoryUtilization();
  long UpTime();
  int TotalProcesses();
  int RunningProcesses();
  std::string Kernel() const;
  std::string OperatingSystem() const;

 private:
  Processor cpu_{};
  std::vector<Process> processes_{};
  const std::string os_;
  const std::string kernel_;
};

#endif
