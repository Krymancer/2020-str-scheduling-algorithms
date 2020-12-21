#include "util.hpp"

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
    std::cout << t.p << " " << t.c << " " << t.d << std::endl;
  }
}

void drawGraph(std::vector<int> schedule, int numberOfTasks) {
  for (int line = 0; line < numberOfTasks; line++) {
    std::cout << "t" << line << " ";
    for (int i = 0; i < schedule.size(); i++) {
      if (schedule[i] == line) {
        std::cout << "#";
      } else {
        std::cout << "-";
      }
      // std::cout << (schedule[i] == line) ? " # " : " - ";
    }
    std::cout << std::endl;
  }
}
