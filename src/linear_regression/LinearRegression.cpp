#include "LinearRegression.hpp"
#include <iostream>
typedef std::vector<double> stdvec;

LinearRegression::LinearRegression(std::string const &path)
{
    dataSet.load(path);
    // cout << std::fixed << dataSet << endl;
    y = dataSet.col(dataSet.n_cols - 1);
    // cout << y << endl;
    X = dataSet.submat(0, 0, dataSet.n_rows - 1, dataSet.n_cols - 2);
    // cout << X << endl;
    X = join_rows(randi<vec>(dataSet.n_rows).ones(), X);
    normalise(X);
}

mat LinearRegression::computeCost(const mat &X, const mat &y, const mat &theta)
{
    return ((double)1 / (2 * (X.n_rows))) * (X * theta - y).t() * (X * theta - y);
}

mat LinearRegression::gradientDescent(const mat &X, const mat &y, const double alpha, const int iterations)
{
    theta = mat(X.n_cols, 1).zeros();

    for (int i = 0; i < iterations; i++)
    {
        theta = theta - alpha * ((double)1 / (X.n_rows)) * X.t() * (X * theta - y);

        // cout << computeCost(X, y, theta) << endl;
        //uncomment the above line if you want to to see how the cost converges.
    }

    cout << theta << endl;

    return theta;
}

std::vector<double> LinearRegression::predict(const std::string &path)
{
    mat x_pred;
    x_pred.load(path);
    x_pred = join_rows(randi<vec>(x_pred.n_rows).ones(), x_pred);
    cout << x_pred << endl;
    cout << theta << endl;
    mat y_pred = x_pred * theta;
    cout << y_pred(0, 0) << endl;
    return conv_to<stdvec>::from(y_pred);
}

void LinearRegression::fit(const double alpha = 0.002, const int iterations = 10000)
{
    std::cout << "here" << std::endl;
    gradientDescent(X, y, alpha, iterations);
}