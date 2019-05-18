#ifndef KNN_HPP_INCLUDED
#define KNN_HPP_INCLUDED
#include <map>
#include <armadillo>
#include <queue>
using namespace arma;
typedef std::pair<double, int> distIndexPair;

class Node
{
public:
  int index;
  Node *left;
  Node *right;

  Node(int i)
  {
    index = i;
    left = right = '\0';
  }
};

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
  mat y_pred;
  int k;
  std::priority_queue<distIndexPair, std::vector<distIndexPair>, std::greater<distIndexPair>> heap;
  Node *KDTreeRoot;
  std::map<int, int> votes;

  double distance(const rowvec &a, const rowvec &b);
  void split(const double train, const double test);
  std::map<int, std::vector<std::pair<int, double>>> distances;
  std::map<int, std::map<double, int>> classVotes;
  static bool sortBySecond(const std::pair<int, double> &, const std::pair<int, double> &);

public:
  Node *insertRec(Node *root, int i, unsigned depth);
  Node *insert(Node *root, int i);
  KNN(std::string const &path, const double train, const double test);
  void getNeighbors(const int k);
  void getResponse();
  void accuracy();
  void fit(int);
  void printtree();
  void printtreerec(Node *);
  void search(int i);
  void searchRec(Node *, int i, unsigned);
  void printHeap();
  void predict();
};

#endif