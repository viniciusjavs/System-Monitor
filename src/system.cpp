#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System()
    : os_(LinuxParser::OperatingSystem()), kernel_(LinuxParser::Kernel()) {}

// Returns the system's CPU.
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes.
vector<Process>& System::Processes() {
  vector<Process> processes;
  for (auto pid : LinuxParser::Pids()) {
    processes.emplace_back(Process{pid});
  }
  return processes_ = processes;
}

// Returns the system's kernel identifier (string).
std::string System::Kernel() const { return kernel_; }

// Returns the system's memory utilization.
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// Returns the operating system name.
std::string System::OperatingSystem() const { return os_; }

// Returns the number of processes actively running on the system.
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// Returns the total number of processes on the system.
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Returns the number of seconds since the system started running.
long System::UpTime() { return LinuxParser::UpTime(); }
