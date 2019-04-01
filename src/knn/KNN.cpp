#include "KNN.hpp"
#include <iostream>

KNN::KNN(std::string const &path, const double train, const double test)
{
    dataSet.load(path);
    y = dataSet.col(dataSet.n_cols - 1);
    X = dataSet.submat(0, 0, dataSet.n_rows - 1, dataSet.n_cols - 2);
    // X = normalise(X);
    X = join_rows(randi<vec>(dataSet.n_rows).ones(), X);

    split(train, test);
}

void KNN::split(const double train, const double test)
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

double KNN::distance(const rowvec &a, const rowvec &b)
{
    rowvec temp = a - b;
    return norm(temp, 2);
}

void KNN::getNeighbors(const int k)
{

    std::vector<std::pair<int, double>> dist;

    int trainLength = X_train.n_rows;
    int testLength = X_test.n_rows;

    for (int i = 0; i < testLength; i++)
    {
        dist.clear();
        for (int j = 0; j < trainLength; j++)
        {
            dist.push_back(std::make_pair(y_train(j), distance(X_test.row(i), X_train.row(j))));
        }
        sort(dist.begin(), dist.end(), KNN::sortBySecond);
        std::vector<std::pair<int, double>> kNeighbors(dist.begin(), dist.begin() + k);
        for (auto x : kNeighbors)
            cout << x.first << " " << x.second << " ";
        cout << endl;
        distances[i] = kNeighbors;
    }
}

bool KNN::sortBySecond(const std::pair<int, double> &a,
                       const std::pair<int, double> &b)
{
    return (a.second < b.second);
}

void KNN::getResponse()
{
    int length = X_test.n_rows;
    for (int i = 0; i < length; i++)
    {
        for (auto x : distances[i])
        {
            classVotes[i][x.first]++;
        }
    }

    for (int i = 0; i < length; i++)
    {
        y_test[i] = classVotes[i].rbegin()->first;
    }

    cout << y_test << endl;
}