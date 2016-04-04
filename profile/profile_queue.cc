/**
 * @file profile_queue.cc
 * @author Omar A Serrano
 * @date 2016-04-03
 */

#include <queue>
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>

#include "queue.hh"

using namespace std;
using namespace chrono;

using high_resolution_time_point = high_resolution_clock::time_point;

inline double getSeconds
  (const high_resolution_time_point &t2,
   const high_resolution_time_point &t1)
{
  return duration_cast<duration<double>>(t2 - t1).count();
}

int main()
{
  int seed = 31;
  auto randEngine = default_random_engine(seed);
  auto uniDist = uniform_int_distribution<>();

  // get times for STL's priority queue
  vector<double> stlValues;
  stlValues.reserve(1000);

  for (int i = 0; i < 1000; ++i)
  {
    priority_queue<int> stlQueue;
    auto t1 = high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j)
    {
      auto r = uniDist(randEngine);
      stlQueue.push(r);
    }

    vector<double> tmpVec;
    tmpVec.reserve(50000);
    for (int j = 0; j < 50000; ++j)
    {
      tmpVec.push_back(stlQueue.top());
      stlQueue.pop();
    }

    auto t2 = high_resolution_clock::now();
    stlValues.push_back(getSeconds(t2, t1));
  }

  // re-seed the engine
  randEngine.seed(seed);

  // get times for my implementation
  vector<double> osppValues;
  osppValues.reserve(1000);

  for (int i = 0; i < 1000; ++i)
  {
    priority_queue<int> osppQueue;
    auto t1 = high_resolution_clock::now();
    for (int j = 0; j < 50000; ++j)
    {
      auto r = uniDist(randEngine);
      osppQueue.push(r);
    }

    vector<double> tmpVec;
    tmpVec.reserve(50000);
    for (int j = 0; j < 50000; ++j)
    {
      tmpVec.push_back(osppQueue.top());
      osppQueue.pop();
    }

    auto t2 = high_resolution_clock::now();
    osppValues.push_back(getSeconds(t2, t1));
  }

  // compute min, max, and mean for STL
  auto stlMinMax = minmax_element(stlValues.begin(), stlValues.end());
  auto stlMean = accumulate(stlValues.begin(), stlValues.end(), 0.0) / stlValues.size();

  // compute min, max, and mean for OSPP
  auto osppMinMax = minmax_element(osppValues.begin(), osppValues.end());
  auto osppMean =
    accumulate(osppValues.begin(), osppValues.end(), 0.0) / osppValues.size();

  // output for STL
  cout << "--------- STL" << endl;
  cout << "min:  " << (*stlMinMax.first) << endl;
  cout << "max:  " << (*stlMinMax.second) << endl;
  cout << "mean: " << stlMean << endl;

  // output for OSPP
  cout << "--------- OSPP" << endl;
  cout << "min:  " << (*osppMinMax.first) << endl;
  cout << "max:  " << (*osppMinMax.second) << endl;
  cout << "mean: " << osppMean << endl;

  return EXIT_SUCCESS;
}
