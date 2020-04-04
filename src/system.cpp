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

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// Returns the system's kernel identifier (string).
std::string System::Kernel() const { return kernel_; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return 0.0; }

// Returns the operating system name.
std::string System::OperatingSystem() const { return os_; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return 0; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return 0; }
