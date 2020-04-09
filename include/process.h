#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid() const;
  std::string User();
  std::string Command();
  float CpuUtilization() const;
  std::string Ram();
  long UpTime();
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

 private:
  int pid_;
};

#endif
