#include "LinearRegression.hpp"
#include <iostream>
typedef std::vector<double> stdvec;

LinearRegression::LinearRegression(std::string const &path, const double train, const double test)
{
    dataSet.load(path);
    y = dataSet.col(dataSet.n_cols - 1);
    X = dataSet.submat(0, 0, dataSet.n_rows - 1, dataSet.n_cols - 2);
    X = join_rows(randi<vec>(dataSet.n_rows).ones(), X);
    theta = mat(X.n_cols, 1).zeros();
    split(train, test);
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

        // cout << computeCost(X, y, theta) << endl;
        //uncomment the above line if you want to to see how the cost converges.
    }

    cout << theta << endl;

    return theta;
}

std::vector<double> LinearRegression::predict()
{
    mat y_pred = X_test * theta;
    cout << y_pred(0, 0) << endl;
    return conv_to<stdvec>::from(y_pred);
}

void LinearRegression::fit(const double &alpha = 0.002, const int &iterations = 10000)
{
    gradientDescent(X, y, alpha, iterations);
}