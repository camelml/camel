#include <iostream>
#include <chrono>
#include "PolynomialRegression.hpp"
using namespace std;
using namespace std::chrono;

int main()
{
     int iterations = 10;
     int size = 100000;
     PolynomialRegression lr("data_100000_clean.csv", 3);
     // lr.scale();
     high_resolution_clock::time_point t1 = high_resolution_clock::now();

     lr.fit(0.008, iterations);

     high_resolution_clock::time_point t2 = high_resolution_clock::now();

     auto duration = duration_cast<microseconds>(t2 - t1).count();

     string testof = "Polynomial Regression\n";
     cout << testof << "Test :\n"
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