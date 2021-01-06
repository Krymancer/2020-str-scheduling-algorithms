#pragma once

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>

#define RM 0
#define DM 1
#define EDF 2

#define ll long long int
/// Return the greatest common divisor of two numbers
int gcd(int a, int b);

/// Return the least common multiple of two numbers
int lcm(int a, int b);

int verifyMethod(const char* method);

/// Struct to represent a task p = period c = computational time d = absolute
/// deadlien rd = relative deadline
typedef struct {
  int id;
  int p, c, d, rd;
  int start, end;
} task;

void printtasks(std::vector<task> tasks);

void printtask(task t);

ll findlcm(int arr[], int n);

void drawGraph(std::vector<int> schedule, int numberOfTasks);

typedef bool (*functioncall)(task t1, task t2);

bool isScheduable(std::vector<task> tasks, functioncall priority, int time);
