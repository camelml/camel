#include <iostream>
#include "Perceptron.hpp"
#include <chrono>
using namespace std::chrono;

using namespace std;

int main()
{
    string path = "data_10000.csv";
    int iterations = 10;
    int size = 100;
    Perceptron lr(path, 80, 20);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    lr.fit(0.1, iterations);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(t2 - t1).count();
    // std::vector<double> predicted = lr.predict();

    string testof = "Perceptron\n";
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