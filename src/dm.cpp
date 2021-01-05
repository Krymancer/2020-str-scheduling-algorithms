#include "dm.hpp"

bool lowerDeadline(task t1, task t2) { return t1.d < t2.d; }

bool dm(std::vector<task> tasks, int time) {
  int n = tasks.size();

  for (int i = 0; i < n; i++) {
    if (tasks[i].d < tasks[i].c) {
      return false;  // Deadline less than computacional time, not schedulable
    }
  }

  std::sort(tasks.begin(), tasks.end(), lowerDeadline);

  std::cout << "Scale: ";

  for (int i = 0; i < tasks.size(); i++) {
    std::cout << "t" << tasks[i].id;
    if (i != (tasks.size() - 1)) {
      std::cout << " => ";
    }
  }

  std::cout << std::endl;

  return isScheduable(tasks, lowerDeadline);
}