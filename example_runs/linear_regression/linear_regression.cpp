#include <iostream>
#include "LinearRegression.hpp"

using namespace std;

int main()
{
    string path = "Salary_Data.csv";
    LinearRegression lr(path);
    lr.fit(0.02, 1000);
    std::vector<double> predicted = lr.predict("pred.csv");

    for (std::vector<double>::const_iterator i = predicted.begin(); i != predicted.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;

    return 0;
}