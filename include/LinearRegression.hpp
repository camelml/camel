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
  mat dataSet;
  mat theta;
  // void normalize(mat mean, mat standardDeviation, mat data);
  mat gradientDescent(const mat &, const mat &, const double, const int);
  mat computeCost(const mat &X, const mat &y, const mat &theta);

public:
  LinearRegression(std::string const &);
  void fit(const double, const int);
  std::vector<double> predict(const std::string &);
};

#endif