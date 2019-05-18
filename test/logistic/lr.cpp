#include <iostream>
#include "LogisticRegression.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    string path = "data_100000.csv";
    int iterations = 1;
    int size = 100000;
    LogisticRegression lr(path, 80, 20);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    lr.fit(0.05, iterations);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(t2 - t1).count();
    // std::vector<double> predicted = lr.predict();

    string testof = "Logistic Regression\n";
    cout << testof << "Test 1:\n"
         << "Dataset size: " << size << endl;
    cout << "Time:" << duration << " microseconds "
         << "or " << duration / 1000.0 << " ms " << endl
         << "Iterations: " << iterations << endl;

    // for (std::vector<double>::const_iterator i = predicted.begin(); i != predicted.end(); ++i)
    //     std::cout << (*i >= 0.5 ? 1 : 0) << '\n';
    // cout << endl;

    lr.accuracy(lr.predict());

    return 0;
}