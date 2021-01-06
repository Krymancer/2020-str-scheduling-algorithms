#include "util.hpp"

#define DEBUG 0

int gcd(int a, int b) {
  for (;;) {
    if (a == 0) return b;
    b %= a;
    if (b == 0) return a;
    a %= b;
  }
}

int lcm(int a, int b) {
  int temp = gcd(a, b);
  return temp ? (a / temp * b) : 0;
}

ll findlcm(int arr[], int n) {
  // Initialize result
  ll ans = arr[0];

  // ans contains LCM of arr[0], ..arr[i]
  // after i'th iteration,
  for (int i = 1; i < n; i++) ans = (((arr[i] * ans)) / (gcd(arr[i], ans)));

  return ans;
}

bool iequals(const std::string& a, const std::string& b) {
  return std::equal(a.begin(), a.end(), b.begin(),
                    [](char a, char b) { return tolower(a) == tolower(b); });
}

int verifyMethod(const char* method) {
  if (iequals(method, "rm")) {
    return RM;
  } else if (iequals(method, "dm")) {
    return DM;
  } else if (iequals(method, "edf")) {
    return EDF;
  } else {
    return -1;
  }
}

void printtasks(std::vector<task> tasks) {
  for (task t : tasks) {
    printtask(t);
  }
}

void printtask(task task) {
  std::cout << "Task " << task.id << " P: " << task.p << " C: " << task.c
            << " D: " << task.d << " RD: " << task.rd << " S: " << task.start
            << " E: " << task.end << std::endl;
}

void drawGraph(std::vector<int> schedule, int numberOfTasks) {
  std::cout << "\n";  // Separator to aesthetics

  for (int line = 0; line < numberOfTasks; line++) {
    std::cout << "t" << line << " ";
    for (int i = 0; i < schedule.size(); i++) {
      std::cout << ((schedule[i] == line) ? "#" : "-");
    }
    std::cout << std::endl;
  }
  std::cout << "   ";
  for (int i = 0; i < schedule.size(); i++) {
    if (i % 10 == 0 && i != 0) {
      std::cout << char(64 + i / 10);
    } else {
      std::cout << i % 10;
    }
  }

  std::cout << "\n" << std::endl;  // Separator to aesthetics
}

bool isScheduable(std::vector<task> tasks, functioncall priority, int time) {
  int n = tasks.size();
  int periods[n];

  std::vector<task> queue;    // Vector for the tasks
  std::vector<int> schedule;  // Stores the schedule

  for (int i = 0; i < tasks.size(); i++) {
    periods[i] = tasks[i].p;
  }

  int period = findlcm(periods, tasks.size());
  if (time != -1) period = time;

  for (int i = 0; i < period; i++) {  // Check for new tasks to add in queue
    for (task t : tasks) {
      if (i % t.p == 0) {  // Task arrived, time = task period
        t.rd = t.d + i;    // Calculate the relative deadline
        t.start = i;
        t.end = t.c;
        queue.push_back(t);
        if (DEBUG) {
          std::cout << "At time: " << i << " added ";
          printtask(t);
        }
      }
    }

    std::sort(queue.begin(), queue.end(), priority);  // Apply the priority

    for (task t : queue) {  // Check for deadlines
      if (t.rd <= i) {      // Deadline reached, scheduled failed
        if (DEBUG) {
          std::cout << "Dadline reached! At time: " << i << " by ";
          printtask(t);
        }
        return false;
      }
    }

    if (queue.size() != 0) {
      if (DEBUG) {
        std::cout << "At time: " << i << " computed ";
        printtask(queue[0]);
      }
      queue[0].end--;
      schedule.push_back(queue[0].id);  // Store in the schedule
    } else {
      schedule.push_back(-1);  // No taks has been processed in this time
    }

    for (int k = 0; k < queue.size(); k++) {  // Check for finished tasks
      if (queue[k].end == 0) {
        if (DEBUG) {
          std::cout << "At time: " << i << " deleted ";
          printtask(queue[k]);
        }
        queue.erase(queue.begin() + k);
      }
    }
  }

  drawGraph(schedule, n);
  return true;
}