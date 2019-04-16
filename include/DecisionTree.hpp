#ifndef DECISIONTREE_HPP_INCLUDED
#define DECISIONTREE_HPP_INCLUDED

#include <armadillo>
#include <iostream>

using namespace arma;

class node
{
    string column_name;
    mat split_data;
    int depth_num;
    bool is_leaf_node=false;
    node left;
    node right;
};
class DecisionTree
{
private:
  node root;
  mat X;
  mat target;
  mat X_train;
  mat y_train;
  mat X_test;
  mat y_test;
  mat dataSet;
  mat split_data;
  mat total_gini;

public:
  DecisionTree(std::string const &path, const int &depth, const int &train_size, const int &test_size);
  void print_tree(node root_node);
  void train_test_split(const double train, const double test);
  float calc_information_gain(mat data, int target_col, int split_col);
  float find_best_column(mat data, int target_col, int cols[]);
  void fit(mat train_data, int target[]);
  void id3(dataSet, target, );
  int* predict(mat test_data);
};

#endif
