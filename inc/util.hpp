#pragma once

#include <algorithm>
#include <iostream>
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
  float p, c, d, rd;
} task;

void printtasks(std::vector<task> tasks);

ll findlcm(int arr[], int n);

void drawGraph(std::vector<int> schedule, int numberOfTasks);
