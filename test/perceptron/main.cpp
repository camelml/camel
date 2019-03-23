#include <iostream>
#include "Perceptron.hpp"

using namespace std;

int main()
{
    string path = "data.csv";
    Perceptron lr(path, 80, 20);
    lr.fit(0.001, 1);
    std::vector<double> predicted = lr.predict();

    // for (std::vector<double>::const_iterator i = predicted.begin(); i != predicted.end(); ++i)
    //     std::cout << (*i >= 0.5 ? 1 : 0) << '\n';
    // cout << endl;

    return 0;
}