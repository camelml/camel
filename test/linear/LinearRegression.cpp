#include "LinearRegression.hpp"
#include <iostream>
#include <math.h>

typedef std::vector<double> stdvec;

LinearRegression::LinearRegression(std::string const &path, const double train, const double test)
{
    dataSet.load(path);
    y = dataSet.col(dataSet.n_cols - 1);
    X = dataSet.submat(0, 0, dataSet.n_rows - 1, dataSet.n_cols - 2);
    // X = normalise(X);
    X = join_rows(randi<vec>(dataSet.n_rows).ones(), X);
    // cout << X << endl;
    theta = mat(X.n_cols, 1).zeros();
    // scale();
    // cout << X << endl;
    // split(train, test);
    X_train = X;
    y_train = y;
    std::cout << std::fixed;
}

void LinearRegression::split(const double train, const double test)
{
    int trainIndex = X.n_rows * (train / (train + test)) - 1;
    X_train = X.submat(0, 0, trainIndex, X.n_cols - 1);
    X_test = X.submat(trainIndex + 1, 0, X.n_rows - 1, X.n_cols - 1);
    y_train = y.submat(0, 0, trainIndex, y.n_cols - 1);
    y_test = y.submat(trainIndex + 1, 0, y.n_rows - 1, y.n_cols - 1);
}

mat LinearRegression::computeCost(const mat &X, const mat &y, const mat &theta)
{
    return ((double)1 / (2 * (X.n_rows))) * (X * theta - y).t() * (X * theta - y);
}

mat LinearRegression::gradientDescent(const mat &X, const mat &y, const double alpha, const int iterations)
{

    for (int i = 0; i < iterations; i++)
    {
        theta = theta - alpha * ((double)1 / (X_train.n_rows)) * X_train.t() * (X_train * theta - y_train);
        // cout << computeCost(X_train, y_train, theta);
    }

    return theta;
}

std::vector<double> LinearRegression::predict()
{
    mat y_pred = (X_train * theta);
    // cout << y_pred(0, 0) << endl;
    accuracy(y_pred);
    return conv_to<stdvec>::from(y_pred);
}

void LinearRegression::fit(const double &alpha, const int &iterations)
{
    gradientDescent(X, y, alpha, iterations);
}

void LinearRegression::scale()
{
    // cout << arma::max(X.col(1)) << endl;
    // cout << arma::mean(X.col(1)) << endl;
    // // cout << arma::stddev(X.col(1)) << endl;
    // means = randi<vec>(X.n_cols).zeros();
    // standardDeviations = randi<vec>(X.n_cols).zeros();

    // for (int i = 1; i < X.n_cols; i++)
    // {
    //     means(i) = arma::max(X.col(i));
    //     standardDeviations(i) = arma::stddev(X.col(i));
    // }

    // for (int i = 0; i < X.n_rows; i++)
    // {
    //     for (int j = 1; j < X.n_cols; j++)
    //     {
    //         X(i, j) = (X(i, j) - means(j)) / standardDeviations(j);
    //         // cout << i << j << endl;
    //     }
    // }

    for (int i = 0; i < y.n_rows; i++)
    {

        y(i) = y(i) / 100;
    }

    // cout << y << endl;
}

void LinearRegression::accuracy(mat &y_pred)
{

    long double error = 0;

    // cout << y_train;
    for (int i = 0; i < y_pred.n_rows; i++)
    {

        error += std::fabs((y_train(i) - y_pred(i)) / y_train(i));
        // if (i == 000)
        // cout << error << endl;
        // cout << std::fabs((y_train(i) - y_pred(i)) / y_train(i)) * 100.0 << endl;
    }
    cout << "size " << y_pred.n_rows << endl;

    cout << error << endl;

    cout << "Sum of errors: " << error << endl;

    cout << "Mean percent of errors: " << error * 100 / y_pred.n_rows << endl;
}