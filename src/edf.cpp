#include "edf.hpp"

bool edf(std::vector<task> tasks) {
  int n = tasks.size();

  float u = 0;
  float x = 0;

  for (int i = 0; i < n; i++) {
    x = tasks[i].c / tasks[i].p;
    u += x;
  }

  if (u <= 1) {
    std::cout << "As " << u << " <= 1" << std::endl
              << "The System is surely Schedulable" << std::endl;
  } else {
    std::cout << "As " << u << " > 1" << std::endl
              << "The System is not Schedulable" << std::endl;
  }

  return isEDFSchedulable(tasks);
}

struct Comparator {
  bool operator()(const task& t1, const task& t2) { return t2.d < t1.d; }
};

bool isEDFSchedulable(std::vector<task> tasks) {
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