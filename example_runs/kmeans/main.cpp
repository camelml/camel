#include <iostream>
#include "KMeans.hpp"

using namespace std;

int main()
{
    string path = "data.csv";
    KMeans lr(path, 3);
    lr.print();
    lr.findMinMax();
    lr.initializeMeans();
    lr.calculateMeans(1);
    lr.findClusters();
    // lr.fit(0.001, 1);
    // std::vector<double> predicted = lr.predict();

    // for (std::vector<double>::const_iterator i = predicted.begin(); i != predicted.end(); ++i)
    //     std::cout << (*i >= 0.5 ? 1 : 0) << '\n';
    // cout << endl;

    return 0;
}