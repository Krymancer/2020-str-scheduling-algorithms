#include "rm.hpp"

bool lowerPeriod(task t1, task t2) { return t1.p < t2.p; }

bool rm(std::vector<task> tasks) {
  int n = tasks.size();
  int i = 0;
  float ut = 0;
  float u = 0;
  float x = 0;
  float y = 0;

  // calculate the utilization
  for (int i = 0; i < n; i++) {
    x = tasks[i].c / tasks[i].p;
    ut += x;
  }

  // calculate value of U
  y = (float)n;
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
        std::cout << " => ";
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

  return isRMSchedulable(tasks);
}

struct Comparator {
  bool operator()(const task& t1, const task& t2) { return t2.p < t1.p; }
};

bool isRMSchedulable(std::vector<task> tasks) {
  int n = tasks.size();

  int periods[n];
  std::priority_queue<task, std::vector<task>, Comparator> qeue;

  std::vector<int> schedule;

  for (int i = 0; i < tasks.size(); i++) {
    periods[i] = tasks[i].p;
  }

  int mmc = findlcm(periods, n);

  for (int i = 0; i < mmc; i++) {
    for (int j = 0; j < n; j++) {
      if ((i % int(tasks[j].p)) == 0) {
        task newtask = tasks[j];
        newtask.d += i;
        qeue.push(newtask);
      }
    }

    if (!qeue.empty()) {
      task task = qeue.top();
      if (task.d <= i) {
        return false;  // Deadline reached, not schedulable
      }

      schedule.push_back(task.id);
      task.c--;
      qeue.pop();
      if (task.c != 0) {
        qeue.push(task);
      }
    } else {
      schedule.push_back(-1);
    }
  }

  drawGraph(schedule, n);
  return true;  // Definitly schedulable
}