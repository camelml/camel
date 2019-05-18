#include "KNN.hpp"
#include <iostream>
#include <functional>

typedef std::pair<double, int> distIndexPair;

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

    y_pred = y_test;
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
        // for (auto x : kNeighbors)
        //     cout << x.first << " " << x.second << " ";
        // cout << endl;
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
        y_pred[i] = classVotes[i].rbegin()->first;
    }

    // cout << y_pred << endl;
}

void KNN::accuracy()
{
    int count = 0;

    for (int i = 0; i < y_test.size(); i++)
    {
        if (y_pred[i] == y_test[i])
            count++;
    }

    cout << "Correct outputs: " << count << endl;
    cout << "Accuracy: " << (count * 1.0 / y_test.size()) * 100 << endl;
}

// KD tree

Node *KNN::insertRec(Node *root, int i, unsigned depth)
{
    if (root == '\0')
        return new Node(i);

    unsigned cd = depth % k;

    if (X_train(i, cd) < X_train(root->index, cd))
        root->left = insertRec(root->left, i, depth + 1);
    else
        root->right = insertRec(root->right, i, depth + 1);

    return root;
}

Node *KNN::insert(Node *root, int i)
{
    return insertRec(root, i, 0);
}

void KNN::fit(int k)
{
    this->k = k;
    KDTreeRoot = new Node(0);
    for (int i = 1; i < X_train.n_rows; i++)
    {
        insert(KDTreeRoot, i);
    }
}

void KNN::searchRec(Node *root, int i, unsigned depth)
{
    if (root == '\0')
        return;
    double dist = distance(X_train.row(root->index), X_test.row(i));
    heap.push(std::make_pair(dist, root->index));
    unsigned cd = depth % k;
    if (X_test(i, cd) < X_train(root->index, cd))
        searchRec(root->left, i, depth + 1);
    else
        searchRec(root->right, i, depth + 1);
}

void KNN::search(int i)
{
    heap = std::priority_queue<distIndexPair, std::vector<distIndexPair>, std::greater<distIndexPair>>();
    searchRec(KDTreeRoot, i, 0);
}

void KNN::printtree()
{
    printtreerec(KDTreeRoot);
}

void KNN::printtreerec(Node *root)
{
    if (root == '\0')
        return;
    // cout << root->index << endl;
    printtreerec(root->left);
    printtreerec(root->right);
}

void KNN::printHeap()
{
}

void KNN::predict()
{
    int count = 0;
    while (!heap.empty() && count < k)
    {
        cout << heap.top().first << " " << heap.top().second << endl;
        votes[y_train[heap.top().second]]++;
        heap.pop();
        count++;
    }

    for (auto elem : votes)
    {
        cout << elem.first << " " << elem.second << endl;
    }
    cout << "predicted value: " << votes.rbegin()->first << endl;
}