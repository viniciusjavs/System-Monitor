#include "processor.h"

using namespace LinuxParser;

// Returns the aggregate CPU utilization.
float Processor::Utilization() {
  std::valarray<long> current_state = CpuUtilization();
  std::valarray<long> cpu_state =
      current_state - cpu_state_;  // 1 sec time frame
  cpu_state_ = current_state;      // update
  // CPU utilization = active jiffies / total jiffies
  return static_cast<float>(ActiveJiffies(cpu_state)) / Jiffies(cpu_state);
}
