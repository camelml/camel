#include "Perceptron.hpp"
#include <iostream>
typedef std::vector<double> stdvec;

Perceptron::Perceptron(std::string const &path, const double train, const double test)
{
    dataSet.load(path);
    y = dataSet.col(dataSet.n_cols - 1);
    X = dataSet.submat(0, 0, dataSet.n_rows - 1, dataSet.n_cols - 2);
    // X = normalise(X);
    X = join_rows(randi<vec>(dataSet.n_rows).ones(), X);

    split(train, test);
}

void Perceptron::split(const double train, const double test)
{
    int trainIndex = X.n_rows * (train / (train + test)) - 1;
    X_train = X.submat(0, 0, trainIndex, X.n_cols - 1);
    X_test = X.submat(trainIndex + 1, 0, X.n_rows - 1, X.n_cols - 1);
    y_train = y.submat(0, 0, trainIndex, y.n_cols - 1);
    y_test = y.submat(trainIndex + 1, 0, y.n_rows - 1, y.n_cols - 1);
}
mat Perceptron::sigmoid(mat const &z)
{
    return (1.0 / (1.0 + exp(-z)));
}

double Perceptron::sigmoid(double const &z)
{
    return (1.0 / (1.0 + exp(-z)));
}

void Perceptron::fit(const double &alpha = 0.002, const int &iterations = 1000)
{
    theta = randi<vec>(X.n_cols).ones().t();
    activation = 0;
    backpropogate(alpha, iterations);
}

double Perceptron::predict(const mat &X, const mat &theta) // private
{

    return (dot(theta, X) > 0) ? 1
                               : 0;
}
void Perceptron::backpropogate(const double &alpha, const int &iterations)
{
    double prediction = 0;
    for (int i = 0; i < iterations; i++)
    {

        for (int i = 0; i < y_train.n_rows; i++)
        {
            // cout << theta << endl;
            theta = theta + alpha * (y_train.row(i) - predict(X_train.row(i), theta)) * (X_train.row(i));
        }
    }
    // cout << theta << endl;
    //  << alpha * (y_train.row(0) - sigmoid(dot(theta.t(), X_train.row(0)))) * X_train.row(0) << endl;
}

std::vector<double> Perceptron::predict() // public
{
    mat y_pred = (X_test * theta.t());
    // cout << "y_pred: \n"
    //      << y_pred;
    return conv_to<stdvec>::from(y_pred);
}

void Perceptron::accuracy(std::vector<double> predicted)
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