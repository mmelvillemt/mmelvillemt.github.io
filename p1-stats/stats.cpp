// stats.cpp
#include "stats.hpp"
#include "p1_library.hpp"
#include <cassert>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

vector<pair<double, int> > summarize(vector<double> v) {
  assert(!v.empty());
  sort(v);
  double current = v.at(0);
  int num = 0;
  vector<pair<double, int>> vec;
  for(size_t i = 0; i < v.size(); ++i){
    if(current == v.at(i)){
        num++;
    } else {
        //cout << current << endl;
        //cout << num << endl;
        vec.push_back({current, num});
        current = v.at(i);
        num = 1;
    }
  }
  vec.push_back({current, num});
  return vec;
}

int count(vector<double> v) {
  assert(!v.empty());
  int count = v.size();
  return count;
}

double sum(vector<double> v) {
  assert(!v.empty());
  double sum = 0;
  for(size_t i = 0; i < v.size(); ++i){
    sum = sum + v.at(i);
  }
  return sum;
}

double mean(vector<double> v) {
  assert(!v.empty());
  double mean = (sum(v) / count(v));
  return mean;
}

double median(vector<double> v) {
  assert(!v.empty());
  sort(v);
  int middle_index = 0;
  int low_index = (count(v) / 2) - 0.5;
  int high_index = (count(v) / 2) + 0.5;
  if(count(v) % 2 == 0){
    return (v.at(low_index) + v.at(high_index)) / 2;
  } else {
    middle_index = count(v) / 2 ;
    return v.at(middle_index);
  }

}

//Figure out tie case
double mode(vector<double> v) {
  assert(!v.empty());
  vector<pair<double, int> > vec = summarize(v);
  double max = vec.at(0).second;
  int max_index = 0;
  for(size_t i = 0; i < vec.size(); ++i){
        if (vec.at(i).second > max) {
            max = vec.at(i).second;
            max_index = i;
        }
    }
  return vec.at(max_index).first;
}

double min(vector<double> v) {
  assert(!v.empty());
  int min = v.at(0); 
  for (size_t i = 1; i < v.size(); ++i) {
        if (v.at(i) < min) {
            min = v.at(i); 
        }
    }
    return min;
}

double max(vector<double> v) {
  assert(!v.empty());
  int max = v.at(0); 
  for (size_t i = 1; i < v.size(); ++i) {
        if (v.at(i) > max) {
            max = v.at(i); 
        }
    }
    return max;
  /**sort(v);
  double max = v.at(count(v) - 1);
  return max;**/
}

double stdev(vector<double> v) {
  assert(!v.empty());
  double d = 0;
  for(size_t i = 0; i < v.size(); ++i){
    d = d + ( (v.at(i) - mean(v)) * (v.at(i) - mean(v)) );
  }
  double stdev;
  if(count(v) != 1){
    stdev = sqrt((d/(count(v) - 1)));
  } else{
    stdev = 0;
  }
  return stdev;
}

double percentile(vector<double> v, double p) {
  assert(!v.empty());
  double n = ((p / 100) * (count(v) - 1)) + 1;
  int k = n;
  double d = n - k;
  double value_p;
  if( d != 0){
    value_p = v.at(k - 1) + (d * (v.at(k) - v.at(k - 1)));
  } else {
    value_p = v.at(k - 1);
  }
  return value_p;
}
