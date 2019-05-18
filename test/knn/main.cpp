#include "KNN.hpp"
#include <chrono>
using namespace std;
using namespace std::chrono;
int main()
{
    std::string path = "data_100000.csv";
    KNN knn(path, 90, 10);
    // knn.fit(2);

    // knn.printHeap();
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    knn.fit(2);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(t2 - t1).count();
    knn.printtree();
    knn.search(1);

    string testof = "KNN\n";
    cout << testof << "Test 1:\n";
    //  << "Dataset size: " << size << endl;
    cout << "Time:" << duration << " microseconds "
         << "or " << duration / 1000.0 << " ms " << endl;
    knn.predict();
}
