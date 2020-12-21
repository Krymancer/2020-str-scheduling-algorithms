#include "dm.hpp"

bool lowerDeadline(task t1, task t2) { return t1.d < t2.d; }

bool dm(std::vector<task> tasks) {
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

  return isDMSchedulable(tasks);
}

struct Comparator {
  bool operator()(const task& t1, const task& t2) { return t2.d < t1.d; }
};

bool isDMSchedulable(std::vector<task> tasks) {
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