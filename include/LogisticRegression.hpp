#ifndef LOGISTICREGRESSION_HPP_INCLUDED
#define LOGISTICREGRESSION_HPP_INCLUDED

#include <iostream>
#include <armadillo>

using namespace arma;

class LogisticRegression
{
  private:
    mat X;
    mat y;
    mat X_train;
    mat y_train;
    mat X_test;
    mat y_test;
    mat dataSet;
    mat theta;

    void split(const double, const double);
    mat sigmoid(mat const &);
    mat gradientDescent(const double &, const int &);
    mat computeCost(const mat &X, const mat &y, const mat &theta);

  public:
    LogisticRegression(std::string const &, const double, const double);
    void fit(const double &, const int &);
    std::vector<double> predict();
};

#endif