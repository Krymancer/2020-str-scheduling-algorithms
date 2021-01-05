#include "main.hpp"

std::vector<task> tasks;
std::ifstream input;

int main(const int argc, const char** argv) {
  if (argc > 4 || argc < 3) {
    std::cout << "Usage: ./app input.file method" << std::endl
              << "Methods:" << std::endl
              << "rm - Rate Monotonic" << std::endl
              << "dm - Deadline Monotonic" << std::endl
              << "edf - Earliest Deadline Frist" << std::endl;
    return -1;
  }

  input.open(argv[1]);
  int i = 0;
  int p, c, d;

  if (!input) {
    std::cerr << "Unable to open file" << std::endl;
    return -1;
  } else {
    std::string line;
    std::getline(input, line);  // Skip frist line
    while (std::getline(input, line)) {
      std::istringstream iss(line);
      iss >> p >> c >> d;

      task t;
      t.c = c;   // Execution Time
      t.p = p;   // Period
      t.d = d;   // Deadline
      t.rd = d;  // Relative deadline
      t.start = 0;
      t.end = 0;
      t.id = i;
      tasks.push_back(t);
      i++;
    }
  }

  int method = verifyMethod(argv[2]);

  int time = -1;
  if (argc == 4) {
    time = atoi(argv[3]);
  }

  switch (method) {
    case RM:
      std::cout << (rm(tasks, time) ? "Schedulable" : "Not schedulable")
                << std::endl;
      break;
    case DM:
      std::cout << (dm(tasks, time) ? "Schedulable" : "Not schedulable")
                << std::endl;
      break;
    case EDF:
      std::cout << (edf(tasks, time) ? "Schedulable" : "Not schedulable")
                << std::endl;
      break;
    default:
      std::cout << "Invalid method" << std::endl;
      break;
  }

  return 0;
}
