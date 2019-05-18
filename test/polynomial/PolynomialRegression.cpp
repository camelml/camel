#include "PolynomialRegression.hpp"
#include <iostream>
#include <armadillo>

typedef std::vector<double> stdvec;

PolynomialRegression::PolynomialRegression(std::string path, int _degree)
{

    degree = _degree;
    // cout << "degree: " << degree << endl;
    dataSet.load(path);
    // cout << "dataset: " << dataSet << endl;
    y = dataSet.col(dataSet.n_cols - 1);
    // cout << "y: " << y << endl;
    mat temp = dataSet.submat(0, 0, dataSet.n_rows - 1, dataSet.n_cols - 3);
    // cout << "X: " << X << endl;
    // X = join_rows(randi<vec>(dataSet.n_rows).ones(), X);
    X = randi<vec>(dataSet.n_rows).ones();
    // cout << "X: " << X << endl;
    for (int i = 1; i <= degree; i++)
    {
        X = join_rows(X, pow(temp, i));
        // cout << X << endl;
    }
}

mat PolynomialRegression::gradientDescent(const mat &X, const mat &y, const double alpha, const int iterations)
{
    theta = mat(X.n_cols, 1).zeros();
    // cout << "theta: " << theta << X << y << endl;
    // cout << X << endl;
    // cout << y << endl;
    // cout << X.t() * (X * theta - y) << endl;

    for (int i = 0; i < iterations; i++)
    {
        theta = theta - alpha * ((double)1 / (X.n_rows)) * X.t() * (X * theta - y);
        // cout << theta << endl;

        // cout << "cost: " << computeCost(X, y, theta) << endl;
        //uncomment the above line if you want to to see how the cost converges.
    }

    // cout << theta << endl;

    return theta;
}

void PolynomialRegression::fit(const double alpha, const int iterations)
{
    // std::cout << "here" << std::endl;
    gradientDescent(X, y, alpha, iterations);
}

std::vector<double> PolynomialRegression::predict(const std::string &path)
{
    // mat temp, x_pred;
    // temp.load(path);
    // x_pred = randi<vec>(x_pred.n_rows).ones();

    // cout << x_pred << endl;
    // cout << theta << endl;
    // mat y_pred = x_pred * theta;
    // cout << y_pred << endl;
    // return conv_to<stdvec>::from(y_pred);

    mat temp, x_pred;
    temp.load(path);
    // cout << temp;
    x_pred = randi<vec>(temp.n_rows).ones();
    // cout << x_pred << endl;
    for (int i = 1; i <= degree; i++)
    {
        x_pred = join_rows(x_pred, pow(temp, i));
        // cout << x_pred << endl;
    }
    mat y_pred = x_pred * theta;
    // cout << y_pred << endl;
    return conv_to<stdvec>::from(y_pred);
}

mat PolynomialRegression::computeCost(const mat &X, const mat &y, const mat &theta)
{
    return ((double)1 / (2 * (X.n_rows))) * (X * theta - y).t() * (X * theta - y);
}

void PolynomialRegression::predict()
{
    mat y_pred = (X * theta);
    // cout << y_pred(0, 0) << endl;
    accuracy(y_pred);
    // return conv_to<stdvec>::from(y_pred);
}

void PolynomialRegression::accuracy(mat &y_pred)
{

    long double error = 0;

    // cout << y_train;
    for (int i = 0; i < y_pred.n_rows; i++)
    {

        error += std::fabs((y(i) - y_pred(i)) / y(i));
        if (i < 10)
            cout << std::fabs((y(i) - y_pred(i)) / y(i)) * 100.0 << endl;
    }
    cout << "size " << y_pred.n_rows << endl;

    cout << error << endl;

    cout << "Sum of errors: " << error << endl;

    cout << "Mean percent of errors: " << error * 100 / y_pred.n_rows << endl;
}