#include "LogisticRegression.hpp"
#include <iostream>
typedef std::vector<double> stdvec;

LogisticRegression::LogisticRegression(std::string const &path, const double train, const double test)
{
    dataSet.load(path);
    y = dataSet.col(dataSet.n_cols - 1);
    X = dataSet.submat(0, 0, dataSet.n_rows - 1, dataSet.n_cols - 2);
    X = join_rows(randi<vec>(dataSet.n_rows).ones(), X);
    scale();
    X_train = X;
    y_train = y;
    theta = mat(X.n_cols, 1).zeros();
    // split(train, test);
}

void LogisticRegression::split(const double train, const double test)
{
    int trainIndex = X.n_rows * (train / (train + test)) - 1;
    X_train = X.submat(0, 0, trainIndex, X.n_cols - 1);
    X_test = X.submat(trainIndex + 1, 0, X.n_rows - 1, X.n_cols - 1);
    y_train = y.submat(0, 0, trainIndex, y.n_cols - 1);
    y_test = y.submat(trainIndex + 1, 0, y.n_rows - 1, y.n_cols - 1);

    // cout << "dataset:  \n"
    //      << dataSet << endl
    //      << "X:  \n"
    //      << X << endl
    //      << "y: \n"
    //      << y << endl
    //      << "X_train:  \n"
    //      << X_train << endl
    //      << "X_test:  \n"
    //      << X_test << endl
    //      << "y_train:  \n"
    //      << y_train << endl
    //      << "y_test:  \n"
    //      << y_test << endl;
}

void LogisticRegression::scale()
{
    // cout << arma::max(X.col(1)) << endl;
    // cout << arma::mean(X.col(1)) << endl;
    // cout << arma::stddev(X.col(1)) << endl;
    means = randi<vec>(X.n_cols).zeros();
    standardDeviations = randi<vec>(X.n_cols).zeros();

    for (int i = 1; i < X.n_cols; i++)
    {
        means(i) = arma::max(X.col(i));
        standardDeviations(i) = arma::stddev(X.col(i));
    }

    for (int i = 0; i < X.n_rows; i++)
    {
        for (int j = 1; j < X.n_cols; j++)
        {
            X(i, j) = (X(i, j) - means(j)) / standardDeviations(j);
            // cout << i << j << endl;
        }
    }

    // cout << X << endl;
}

mat LogisticRegression::sigmoid(mat const &z)
{
    return (1.0 / (1.0 + exp(-z)));
}

void LogisticRegression::fit(const double &alpha = 0.002, const int &iterations = 10000)
{
    // std::cout << "here" << std::endl;
    gradientDescent(alpha, iterations);
}

mat LogisticRegression::gradientDescent(const double &alpha, const int &iterations)
{

    for (int i = 0; i < iterations; i++)
    {
        theta = theta - alpha * ((double)1 / (X_train.n_rows)) * X_train.t() * (sigmoid(X_train * theta) - y_train);

        // cout << ((double)-1 / X_train.n_rows) * (y_train.t() * log(sigmoid(X_train * theta)) + (1 - y_train.t()) * log(1 - sigmoid(X_train * theta)));
    }

    // cout << theta << endl;

    return theta;
}

std::vector<double> LogisticRegression::predict()
{
    mat y_pred = sigmoid(X_train * theta);
    // cout << "y_pred: \n"
    //      << y_pred;
    return conv_to<stdvec>::from(y_pred);
}

void LogisticRegression::accuracy(std::vector<double> predicted)
{
    int count = 0;

    for (int i = 0; i < predicted.size(); i++)
    {
        if (y_train[i] == (predicted[i] >= 0.5 ? 1 : 0))
            count++;
    }

    cout << "Correct outputs: " << count << endl;
    cout << "Accuracy: " << (count * 1.0 / predicted.size()) * 100 << endl;
}