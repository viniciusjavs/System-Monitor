#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, std::string user);
  int Pid() const;
  std::string User() const;
  std::string Command();
  float CpuUtilization() const;
  std::string Ram();
  long UpTime();
  bool operator<(Process const& a) const;

 private:
  int pid_;
  const std::string user_;
};

#endif
