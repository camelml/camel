#ifndef DECISIONTREE_HPP_INCLUDED
#define DECISIONTREE_HPP_INCLUDED

#include <armadillo>
#include <iostream>

using namespace arma;

class node
{
    string column_name;
    int depth_num;
    node left;
    node right;
};
class DecisionTree
{
private:
  mat dataSet;
  mat split_data;
  mat total_gini;

public:
  DecisionTree(std::string const &path, const int &depth);
  void print_tree();
  void train_tree();
  void fit(mat train_data, int target[]);
  int gigni_score();
  int* predict(mat test_data);
};

#endif
