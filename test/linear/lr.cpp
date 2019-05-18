#include <iostream>
#include <chrono>
#include "LinearRegression.hpp"
using namespace std;
using namespace std::chrono;

int main()
{
     int iterations = 1;
     int size = 10000;
     LinearRegression lr("data_10000_clean.csv", 50, 50);
     lr.scale();
     high_resolution_clock::time_point t1 = high_resolution_clock::now();

     lr.fit(0.1, iterations);

     high_resolution_clock::time_point t2 = high_resolution_clock::now();

     auto duration = duration_cast<microseconds>(t2 - t1).count();

     string testof = "Multivariate Linear Regression\n";
     cout << testof << "Test 4:\n"
          << "Dataset size: " << size << endl;
     cout << "Time:" << duration << " microseconds "
          << "or " << duration / 1000.0 << " ms " << endl
          << "Iterations: " << iterations << endl;

     lr.predict();

     // for (int i = 0; i < 10; i++)
     // {
     //     cout << v[i] << endl;
     // }

     // lr.accuracy(lr.predict());

     cout << endl;

     return 0;
}