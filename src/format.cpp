#include "format.h"

#include <chrono>
#include <iomanip>
#include <sstream>

using std::chrono::duration_cast;

/*
  Receives a long int measuring seconds.
  Returns a string in the following format: HH:MM:SS
*/
std::string Format::ElapsedTime(long seconds) {
  std::chrono::seconds sec(seconds);
  constexpr int max = 100;  // maximum hours until reset
  auto h = duration_cast<std::chrono::hours>(sec);
  sec -= h;
  auto min = duration_cast<std::chrono::minutes>(sec);
  sec -= min;
  std::ostringstream sstream;
  sstream << std::setw(2) << std::setfill('0') << h.count() % max << ":"
          << std::setw(2) << std::setfill('0') << min.count() << ":"
          << std::setw(2) << std::setfill('0') << sec.count();
  return sstream.str();
}
