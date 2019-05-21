#include "KMeans.hpp"
#include <iostream>
#include <math.h>

KMeans::KMeans(std::string const &path, const int &k)
{
    dataSet.load(path);
    this->k = k;
}

void KMeans::print()
{
    cout << "dataset: " << dataSet << endl
         << "k:" << k << endl;
}

void KMeans::findMinMax()
{
    extremas = zeros<mat>(2, dataSet.n_cols);
    // cout << extremas << endl;
    int i = 0;

    for (mat::iterator it = extremas.begin(); it != extremas.end(); ++it)
    {

        *it = arma::min(dataSet.col(i));
        it++;
        *it = arma::max(dataSet.col(i));
        i++;
    }
    // cout << extremas << endl;
}

void KMeans::initializeMeans()
{
    means = zeros<mat>(k, dataSet.n_cols);

    for (int i = 0; i < means.n_rows; i++)
    {
        for (int j = 0; j < means.n_cols; j++)
        {
            means(i, j) = randi(distr_param(extremas(0, j), extremas(1, j)));
        }
    }
    // cout << "means:" << means << endl;
}

double KMeans::distance(rowvec a, rowvec b)
{
    rowvec temp = a - b;
    return norm(temp, 2);
}

void KMeans::updateMean(int size, int i, int index)
{
    for (int j = 0; j < means.row(index).n_elem; j++)
    {
        means.row(index)(j) = (means.row(index)(j) * (size - 1) + dataSet.row(i)(j)) / size;
    }
    // cout << centroid << endl;
}

int KMeans::classify(const rowvec &point)
{
    double minimum = INT_MAX;
    int index = -1;

    // cout << "in classify" << endl
    //      << "point " << point << endl;

    for (int i = 0; i < means.n_rows; i++)
    {
        double dist = distance(point, means.row(i));
        // cout << dist << endl;
        if (dist < minimum)
        {
            minimum = dist;
            index = i;
        }
    }

    return index;
}

void KMeans::calculateMeans(int iterations)
{
    clusterSizes = zeros<rowvec>(k);
    belongsTo = zeros<rowvec>(dataSet.n_rows);
    // cout << "looping.." << endl;

    for (int i = 0; i < iterations; i++)
    {
        bool noChange = true;
        for (int i = 0; i < dataSet.n_rows; i++)
        {
            // cout << "1\n";
            int index = classify(dataSet.row(i));
            // cout << "2\n"
            //      << index << endl;
            // cout << clusterSizes << endl;
            clusterSizes(index) += 1;
            // cout << "mean1: " << means << endl;
            updateMean(clusterSizes(index), i, index);
            // cout << "mean2: " << means << endl;
            if (index != belongsTo[i])
                noChange = false;
            belongsTo[i] = index;
        }
        if (noChange)
            break;
    }
}

void KMeans::findClusters()
{
    clusters = zeros<vec>(dataSet.n_rows);
    for (int i = 0; i < dataSet.n_rows; i++)
    {
        clusters(i) = classify(dataSet.row(i));
    }
    cout << clusters << endl;
}