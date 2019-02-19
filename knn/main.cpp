#include <iostream>
#include <armadillo>
#include "../lib/libfast_knn.h"

using arma::rowvec;

int main() 
{
	FastKNN datatest;
// http://archive.ics.uci.edu/ml/datasets/Iris - change last col to number... each number is a diferent class
	datatest.train("datasets/iris.data");

	rowvec X1, X2, X3, X4, X5;
	X1 << 5.0 << 3.0 << 1.6 << 0.2 << endr;
	X2 << 1.0 << 2.0 << 1.6 << 2.2 << endr;
	X3 << 6.0 << 4.0 << 4.6 << 3.2 << endr;
	X4 << 0.9 << 1.0 << 2.6 << 2.2 << endr;
	X5 << 9.0 << 7.0 << 4.6 << 4.2 << endr;
	
    cout << "Test Manhattan:" << endl;
    cout << "1: " << X1 << "\tResult: " << datatest.Classify("manhattan", X1, 10) << endl;
    cout << "2: " << X2 << "\tResult: " << datatest.Classify("manhattan", X2, 10) << endl;
    cout << "3: " << X3 << "\tResult: " << datatest.Classify("manhattan", X3, 10) << endl;
    cout << "4: " << X4 << "\tResult: " << datatest.Classify("manhattan", X4, 10) << endl;
    cout << "5: " << X5 << "\tResult: " << datatest.Classify("manhattan", X5, 10) << endl;
	cout << "\n";

    cout << "Test Euclidean:" << endl;
    cout << "1: " << X1 << "\tResult: " << datatest.Classify("euclidean", X1, 10) << endl;
	cout << "2: " << X2 << "\tResult: " << datatest.Classify("euclidean", X2, 10) << endl;
	cout << "3: " << X3 << "\tResult: " << datatest.Classify("euclidean", X3, 10) << endl;
	cout << "4: " << X4 << "\tResult: " << datatest.Classify("euclidean", X4, 10) << endl;
	cout << "5: " << X5 << "\tResult: " << datatest.Classify("euclidean", X5, 10) << endl;
	cout << "\n";
	
	return 0;
}
