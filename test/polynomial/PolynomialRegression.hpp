#ifndef POLYNOMIALREGRESSION_HPP_INCLUDED
#define POLYNOMIALREGRESSION_HPP_INCLUDED

#include <armadillo>
#include <iostream>

using namespace arma;

class PolynomialRegression
{
private:
  int degree;
  mat X;
  mat y;
  mat dataSet;
  mat theta;
  mat gradientDescent(const mat &, const mat &, const double, const int);
  mat computeCost(const mat &, const mat &, const mat &);

public:
  void predict();
  void accuracy(mat &);
  PolynomialRegression(std::string, int);
  void fit(const double, const int);
  std::vector<double> predict(const std::string &);
};

#endif