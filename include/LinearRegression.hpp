#ifndef LINEARREGRESSION_HPP_INCLUDED
#define LINEARREGRESSION_HPP_INCLUDED

#include <armadillo>
#include <iostream>

using namespace arma;

class LinearRegression
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

  // void normalize(mat mean, mat standardDeviation, mat data);
  mat gradientDescent(const mat &, const mat &, const double, const int);
  mat computeCost(const mat &X, const mat &y, const mat &theta);

public:
  LinearRegression(std::string const &, const double, const double);
  void fit(const double &, const int &);
  std::vector<double> predict();
};

#endif