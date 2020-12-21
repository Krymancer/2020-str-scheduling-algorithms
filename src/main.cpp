#include "main.hpp"

std::vector<task> tasks;
std::ifstream input;

int main(const int argc, const char** argv) {
  if (argc != 3) {
    std::cout << "Usage: ./app input.file method" << std::endl
              << "Methods:" << std::endl
              << "rm - Rate Monotonic" << std::endl
              << "dm - Deadline Monotonic" << std::endl
              << "edf - Earliest Deadline Frist" << std::endl;
    return -1;
  }

  input.open(argv[1]);
  int i = 0;
  float p, c, d;

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
      t.c = c;  // Execution Time
      t.p = p;  // Period
      t.d = d;  // Deadline
      t.id = i;
      tasks.push_back(t);
      i++;
    }
  }

  int method = verifyMethod(argv[2]);

  switch (method) {
    case RM:
      std::cout << (rm(tasks) ? "Schedulable" : "Not schedulable") << std::endl;
      break;
    case DM:
      std::cout << (dm(tasks) ? "Schedulable" : "Not schedulable") << std::endl;
      break;
    case EDF:
      std::cout << (edf(tasks) ? "Schedulable" : "Not schedulable")
                << std::endl;
      break;
    default:
      std::cout << "Invalid method" << std::endl;
      break;
  }

  return 0;
}
