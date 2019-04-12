#include "DecisionTree.hpp"
#include <iostream>
typedef std::vector<double> stdvec;

DecisionTree::DecisionTree(std::string const &path, const int depth, const int train_size, const int test_size)
{
    dataSet.load(path);
    target = dataSet.col(dataSet.n_cols - 1);
    X = dataSet.submat(0, 0, dataSet.n_rows - 1, dataSet.n_cols - 2);
    train_test_split(train_size, test_size);
}
void DecisionTree::train_test_split(const double train, const double test)
{
    int trainIndex = X.n_rows * (train / (train + test)) - 1;
    X_train = X.submat(0, 0, trainIndex, X.n_cols - 1);
    X_test = X.submat(trainIndex + 1, 0, X.n_rows - 1, X.n_cols - 1);
    y_train = target.submat(0, 0, trainIndex, target.n_cols - 1);
    y_test = target.submat(trainIndex + 1, 0, target.n_rows - 1, y.n_cols - 1);
}
float DecisionTree::entropy_score(int col)
{
    //Calculate entropy given a column number.
    //Compute the counts of each unique value in the column
    //Divide by the total column length to get a probability
}
float DecisionTree::calc_information_gain(mat data, int target_col, int split_col)
{

    //loop through the data and provide column with maximum information gain
}
float DecisionTree::find_best_column(mat data, int target_col, int cols[])
{

}
