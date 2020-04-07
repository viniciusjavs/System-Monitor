#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid) {}

// Returns this process's ID.
int Process::Pid() const { return pid_; }

// Return this process's CPU utilization.
float Process::CpuUtilization() const {
  // Process CPU utilization = spent seconds / total seconds
  return (LinuxParser::ActiveJiffies(pid_) / sysconf(_SC_CLK_TCK)) /
         static_cast<float>(LinuxParser::UpTime() - LinuxParser::UpTime(pid_));
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// Returns the user (name) that generated this process.
string Process::User() { return LinuxParser::User(pid_); }

// Returns the age of this process (in seconds).
long Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }
