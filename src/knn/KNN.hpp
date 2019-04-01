#ifndef KNN_HPP_INCLUDED
#define KNN_HPP_INCLUDED
#include <map>
#include <armadillo>
using namespace arma;

class KNN
{
  private:
    mat dataSet;
    mat X;
    mat y;
    mat X_train;
    mat y_train;
    mat X_test;
    mat y_test;
    double distance(const rowvec &a, const rowvec &b);
    void split(const double train, const double test);
    std::map<int, std::vector<std::pair<int, double>>> distances;
    std::map<int, std::map<double, int>> classVotes;
    static bool sortBySecond(const std::pair<int, double> &, const std::pair<int, double> &);

  public:
    KNN(std::string const &path, const double train, const double test);
    void getNeighbors(const int k);
    void getResponse();
};

#endif