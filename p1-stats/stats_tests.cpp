/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_count_small_data_set();
void test_sum_small_data_set();
void test_mean_small_data_set();
void test_min_small_data_set();
void test_max_small_data_set();
void test_median_small_data_set();
void test_stdev_small_data_set();
void test_summarize_small_data_set();
void test_mode_small_data_set_1();
void test_mode_small_data_set_2();
void test_percentile_small_data_set();

void test_count_small_data_single();
void test_sum_small_data_single();
void test_mean_small_data_single();
void test_min_small_data_single();
void test_max_small_data_single();
void test_median_small_data_single();
void test_stdev_small_data_single();
void test_summarize_small_data_single();
void test_mode_small_data_single();
void test_percentile_small_data_single();
// Add prototypes for you test functions here.

int main() {
  test_count_small_data_set();
  test_sum_small_data_set();
  test_mean_small_data_set();
  test_min_small_data_set();
  test_max_small_data_set();
  test_median_small_data_set();
  test_stdev_small_data_set();
  test_summarize_small_data_set();
  test_mode_small_data_set_1();
  test_mode_small_data_set_2();
  test_percentile_small_data_set();

  test_count_small_data_single();
  test_sum_small_data_single();
  test_mean_small_data_single();
  test_min_small_data_single();
  test_max_small_data_single();
  test_median_small_data_single();
  test_stdev_small_data_single();
  test_summarize_small_data_single();
  test_mode_small_data_single();
  test_percentile_small_data_single();
  // Call your test functions here

  return 0;
}

void test_count_small_data_set() {
  cout << "test_count_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(-1);

  assert(count(data) == 10);

  cout << "PASS!" << endl;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(5);
  data.push_back(8);
  data.push_back(9);
  data.push_back(-4);

  assert(sum(data) == 24);

  cout << "PASS!" << endl;
}

void test_mean_small_data_set() {
  cout << "test_mean_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(mean(data) == 2);

  cout << "PASS!" << endl;
}

void test_min_small_data_set() {
  cout << "test_min_small_data_set" << endl;

  vector<double> data;
  data.push_back(3);
  data.push_back(2);
  data.push_back(1);

  assert(min(data) == 1);

  cout << "PASS!" << endl;
}

void test_max_small_data_set() {
  cout << "test_max_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(max(data) == 3);

  cout << "PASS!" << endl;
}
// Add the test function implementations here.

void test_median_small_data_set() {
  cout << "test_median_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);

  //cout << median(data) << endl;
  assert(median(data) == 2.5);

  cout << "PASS!" << endl;
}

void test_stdev_small_data_set() {
  cout << "test_stdev_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  /**data.push_back(6);
  data.push_back(9);
  data.push_back(2);**/

  //cout << stdev(data) << endl;
  assert(stdev(data) == 1);

  cout << "PASS!" << endl;
}

void test_summarize_small_data_set() {
  cout << "test_summarize_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  /**data.push_back(1);
  data.push_back(8);
  data.push_back(9);
  data.push_back(1);
  data.push_back(2);
  data.push_back(5);**/

  vector<pair<double, int> > vec = summarize(data);
  cout << vec.at(0).first << endl;
  cout << vec.at(0).second << endl;
  cout << vec.at(1).first << endl;
  cout << vec.at(1).second << endl;
  cout << vec.at(2).first << endl;
  cout << vec.at(2).second << endl;


  cout << "PASS!" << endl;
}

void test_mode_small_data_set_1() {
  cout << "test_mode_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(3);

  //cout << mode(data) << endl;
  assert(mode(data) == 3);

  cout << "PASS!" << endl;
}

void test_mode_small_data_set_2() {
  cout << "test_mode_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(3);
  data.push_back(2);

  assert(mode(data) == 2);

  cout << "PASS!" << endl;
}

void test_percentile_small_data_set() {
  cout << "test_percentile_small_data_set" << endl;

  vector<double> data;
  data.push_back(15);
  data.push_back(20);
  data.push_back(35);
  data.push_back(40);
  data.push_back(50);

  //cout << percentile(data, 40) << endl;
  assert(percentile(data, 40) == 29);

  cout << "PASS!" << endl;
}

void test_count_small_data_single() {
  cout << "test_count_small_data_single" << endl;

  vector<double> data;
  data.push_back(1);

  assert(count(data) == 1);

  cout << "PASS!" << endl;
}

void test_sum_small_data_single() {
  cout << "test_sum_small_data_single" << endl;

  vector<double> data;
  data.push_back(1);

  assert(sum(data) == 1);

  cout << "PASS!" << endl;
}

void test_mean_small_data_single() {
  cout << "test_mean_small_data_single" << endl;

  vector<double> data;
  data.push_back(1);

  assert(mean(data) == 1);

  cout << "PASS!" << endl;
}

void test_min_small_data_single() {
  cout << "test_min_small_data_single" << endl;

  vector<double> data;
  data.push_back(1);

  assert(min(data) == 1);

  cout << "PASS!" << endl;
}

void test_max_small_data_single() {
  cout << "test_max_small_data_single" << endl;

  vector<double> data;
  data.push_back(1);

  assert(max(data) == 1);

  cout << "PASS!" << endl;
}
// Add the test function implementations here.

void test_median_small_data_single() {
  cout << "test_median_small_data_single" << endl;

  vector<double> data;
  data.push_back(1);

  //cout << median(data) << endl;
  assert(median(data) == 1);

  cout << "PASS!" << endl;
}

void test_stdev_small_data_single() {
  cout << "test_stdev_small_data_single" << endl;

  vector<double> data;
  data.push_back(1);

  //cout << stdev(data) << endl;
  assert(stdev(data) == 0);

  cout << "PASS!" << endl;
}

void test_summarize_small_data_single() {
  cout << "test_summarize_small_data_single" << endl;

  vector<double> data;
  data.push_back(1);
 

  vector<pair<double, int> > vec = summarize(data);
  //cout << vec.at(0).first << endl;
  //cout << vec.at(0).second << endl;

  cout << "PASS!" << endl;
}

void test_mode_small_data_single() {
  cout << "test_mode_small_data_single" << endl;

  vector<double> data;
  data.push_back(1);

  assert(mode(data) == 1);

  cout << "PASS!" << endl;
}

void test_percentile_small_data_single() {
  cout << "test_percentile_small_data_single" << endl;

  vector<double> data;
  data.push_back(15);

  //cout << percentile(data, 40) << endl;
  assert(percentile(data, 40) == 15);

  cout << "PASS!" << endl;
}