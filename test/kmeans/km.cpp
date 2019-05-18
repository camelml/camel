#include <iostream>
#include "camel/KMeans.hpp"
#include <chrono>
using namespace std::chrono;

using namespace std;

int main()
{
    string path = "data_100000.csv";
    int size = 100000;
    KMeans lr(path, 2);
    // lr.print();
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    lr.findMinMax();

    lr.initializeMeans();
    lr.calculateMeans(1);
    lr.findClusters();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(t2 - t1).count();
    string testof = "KMEANS\n";
    cout << testof << "Test 1:\n"
         << "Dataset size: " << size << endl;
    cout << "Time:" << duration << " microseconds "
         << "or " << duration / 1000.0 << " ms " << endl;

    return 0;
}
