#ifndef KMEANS_HPP_INCLUDED
#define KMEANS_HPP_INCLUDED

#include <armadillo>
using namespace arma;

class KMeans
{
private:
  // mat X;
  // mat y;
  // mat X_train;
  // mat y_train;
  // mat X_test;
  // mat y_test;
  mat dataSet;
  mat extremas;
  int k;
  int min;
  int max;
  mat means;
  vec clusters;
  rowvec clusterSizes;
  rowvec belongsTo;

public:
  KMeans(std::string const &path, const int &k);
  void print();
  void findMinMax();
  void initializeMeans();
  double distance(rowvec a, rowvec b);
  void updateMean(int size, int,int);
  int classify(const rowvec &point);
  void calculateMeans(int iterations);
  void findClusters();
};

#endif