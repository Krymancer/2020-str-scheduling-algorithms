#include "edf.hpp"

bool lowerRealtiveDeadline(task t1, task t2) { return t1.rd < t2.rd; }

bool edf(std::vector<task> tasks, int time) {
  int n = tasks.size();

  double u = 0;
  double x = 0;

  for (int i = 0; i < n; i++) {
    x = (double)tasks[i].c / (double)tasks[i].p;
    u += x;
  }

  if (u <= 1) {
    std::cout << "As " << u << " <= 1" << std::endl
              << "The System is not surely Schedulable" << std::endl;
  } else {
    std::cout << "As " << u << " > 1" << std::endl
              << "The System is not Schedulable" << std::endl;
  }

  return isScheduable(tasks, lowerRealtiveDeadline);
}