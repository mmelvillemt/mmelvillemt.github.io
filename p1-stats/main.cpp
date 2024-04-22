// main.cpp
#include "stats.hpp"
#include "p1_library.hpp"
#include <iostream>

using namespace std;

int main() {
  cout << "enter a filename" << endl;
  string filename;
  cin >> filename;
  cout << "enter a column name" << endl;
  string column_name;
  cin >> column_name;
  cout << "reading column " << column_name << " from " << filename << endl;
  vector<double> v = extract_column(filename, column_name);

  vector<pair<double, int> > vec = summarize(v);
  cout << "Summary (value: frequency)" << endl;
  for (size_t i=0; i < vec.size(); ++i) {
  cout << vec.at(i).first << ": " << vec.at(i).second << "\n";
  }
  cout << "\n";
  cout << "count = " << count(v) << endl;
  cout << "sum = " << sum(v) << endl;
  cout << "mean = " << mean(v) << endl;
  cout << "stdev = " << stdev(v) << endl;
  cout << "median = " << median(v) << endl;
  cout << "mode = " << mode(v) << endl;
  cout << "min = " << min(v) << endl;
  cout << "max = " << max(v) << endl;
  cout << "  0th percentile = " << percentile(v, 0) << endl;
  cout << " 25th percentile = " << percentile(v, 25) << endl;
  cout << " 50th percentile = " << percentile(v, 50) << endl;
  cout << " 75th percentile = " << percentile(v, 75) << endl;
  cout << "100th percentile = " << percentile(v, 100) << endl;

}

