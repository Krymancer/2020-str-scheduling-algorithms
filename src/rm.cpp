#include "rm.hpp"

bool lowerPeriod(task t1, task t2) { return t1.p < t2.p; }

bool rm(std::vector<task> tasks, int time) {
  int n = tasks.size();
  int i = 0;
  double ut = 0;
  double u = 0;
  double x = 0;
  double y = 0;

  // calculate the utilization
  for (int i = 0; i < n; i++) {
    x = (double)tasks[i].c / (double)tasks[i].p;
    ut += x;
  }

  // calculate value of U
  y = (double)n;
  y = y * ((pow(2.0, 1 / y)) - 1);
  u = y;

  std::sort(tasks.begin(), tasks.end(), lowerPeriod);

  if (ut < u) {
    std::cout << "As " << ut << " < " << u << std::endl
              << "The System is surely Schedulable" << std::endl
              << "Scale: ";

    for (i = 0; i < tasks.size(); i++) {
      std::cout << "t" << tasks[i].id;
      if (i != (tasks.size() - 1)) {
        std::cout << " → ";
      }
    }

    std::cout << std::endl;

  } else {
    std::cout << "As " << ut << " >= " << u << std::endl
              << "The System is not surely Schedulable" << std::endl
              << "Scale: ";

    for (i = 0; i < tasks.size(); i++) {
      std::cout << "t" << tasks[i].id;
      if (i != (tasks.size() - 1)) {
        std::cout << " => ";
      }
    }
    std::cout << std::endl;
  }
  return isScheduable(tasks, lowerPeriod);
}