#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <limits>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// Reads the operating system name from the filesystem.
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open())
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      if (linestream >> key >> value)
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
    }
  return {};
}

// Reads and returns the kernel version.
string LinuxParser::Kernel() {
  string os, _, kernel{};
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> _ >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Reads and returns the system memory utilization.
float LinuxParser::MemoryUtilization() {
  long total{1}, free{}, buffers{}, cached{}, sreclaimable{}, shmem{};
  long used;
  string line;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      string key;
      long value;
      std::istringstream linestream(line);
      if (linestream >> key >> value) {
        key.pop_back();
        if (key == "MemTotal")
          total = value;
        else if (key == "MemFree")
          free = value;
        else if (key == "Buffers")
          buffers = value;
        else if (key == "Cached")
          cached = value;
        else if (key == "SReclaimable")
          sreclaimable = value;
        else if (key == "Shmem")
          shmem = value;
      }
    }
  }
  // htop formula
  used = total - free;
  cached += sreclaimable - shmem;
  return static_cast<float>(used - buffers - cached) / total;
}

// Reads and returns the system uptime.
long LinuxParser::UpTime() {
  long up_time{};
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up_time;
  }
  return up_time;
}

// Reads and returns the number of jiffies for the system.
long LinuxParser::Jiffies(const std::valarray<long>& cpu_state) {
  return ActiveJiffies(cpu_state) + IdleJiffies(cpu_state);
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// Reads and returns the number of active jiffies for the system.
inline long LinuxParser::ActiveJiffies(const std::valarray<long>& cpu_state) {
  // cpu_state[kUser_] =  user + guest
  // cpu_state[kNice_] = nice + guest_nice
  // cpu_state[kSystem_] + cpu_state[kIRQ_] + cpu_state[kSoftIRQ_] = system
  return cpu_state[kUser_] + cpu_state[kNice_] + cpu_state[kSystem_] +
         cpu_state[kIRQ_] + cpu_state[kSoftIRQ_] + cpu_state[kSteal_];
}

// Reads and returns the number of idle jiffies for the system.
inline long LinuxParser::IdleJiffies(const std::valarray<long>& cpu_state) {
  // cpu_state[kIdle_] + cpu_state[kIOwait_] = idle
  return cpu_state[kIdle_] + cpu_state[kIOwait_];
}

// Reads and returns CPU utilization.
std::valarray<long> LinuxParser::CpuUtilization() {
  std::valarray<long> cpu_state(szCPUStates_);
  string line;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    std::istream_iterator<string> linestream_iter(linestream);  // read first
    std::for_each(std::begin(cpu_state), std::end(cpu_state),
                  [&linestream](auto& elem) { linestream >> elem; });
  }
  return cpu_state;
}

// Reads and returns the total number of processes.
int LinuxParser::TotalProcesses() {
  std::string word;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, word, ' ')) {
      if (word != "processes") {
        filestream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else {
        std::getline(filestream, word);
        return std::stoi(word);
      }
    }
  }
  return 0;
}

// Reads and returns the number of running processes.
int LinuxParser::RunningProcesses() {
  std::string word;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, word, ' ')) {
      if (word != "procs_running") {
        filestream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else {
        std::getline(filestream, word);
        return std::stoi(word);
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
