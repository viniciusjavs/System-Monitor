#include "system.h"

#include <unistd.h>

#include <cstddef>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;

System::System()
    : os_(LinuxParser::OperatingSystem()), kernel_(LinuxParser::Kernel()) {}

// Returns the system's CPU.
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes.
set<Process>& System::Processes() {
  set<Process> processes;
  for (auto pid : LinuxParser::Pids()) {
      processes.emplace(Process{pid, LinuxParser::User(pid)});
  }
  // std::sort(std::begin(processes), std::end(processes));
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
