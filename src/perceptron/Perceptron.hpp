#ifndef PERCEPTRON_HPP_INCLUDED
#define PERCEPTRON_HPP_INCLUDED

#include <armadillo>
using namespace arma;

class Perceptron
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
  double activation;

  void split(const double, const double);
  mat sigmoid(mat const &);
  double sigmoid(double const &);
  void backpropogate(const double &, const int &);
  double predict(const mat &X, const mat &theta);

public:
  Perceptron(std::string const &, const double, const double);
  void fit(const double &, const int &);
  std::vector<double> predict();
};

#endif
