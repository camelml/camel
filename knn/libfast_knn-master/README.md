# libfast_knn
C++ library of k-nearest neighbors algorithm (k-NN), faster because uses Armadillo lib

In pattern recognition, the k-nearest neighbors algorithm (k-NN) is a non-parametric method used for classification and regression.[1] In both cases, the input consists of the k closest training examples in the feature space. The output depends on whether k-NN is used for classification or regression: 

In k-NN classification, the output is a class membership. An object is classified by a majority vote of its neighbors, with the object being assigned to the class most common among its k nearest neighbors (k is a positive integer, typically small). If k = 1, then the object is simply assigned to the class of that single nearest neighbor.

*Description by wikipedia* see more here https://en.wikipedia.org/wiki/K-nearest\_neighbors\_algorithm

## Why uses this C++ library ?

So this library uses Armadillo, armadillo uses high optimizations with BLAS, LAPACK, SIMD, OpenMP etc... if you need performance take it... 

Configs options http://arma.sourceforge.net/docs.html#config_hpp


## Example:

Install armadillo lib, at debian distros based follow this command:

```
$ apt-get install libarmadillo-dev
```

Look the file "src/main.cpp", to run you can follow this command.

```
cooler@Nepal:~/codes/libfast_knn$ make
g++ -Wall -O3 -larmadillo -fstack-protector-all -D_FORTIFY_SOURCE=2 -c src/*.cpp -c lib/*.h -c lib/*.cpp
g++ -o bin/knn_test *.o -Wl,-z,relro,-z,now 
rm *.o

cooler@Nepal:~/codes/libfast_knn$ bin/knn_test 
Test Manhattan:
1:    5.0000   3.0000   1.6000   0.2000
	Result: 1
2:    1.0000   2.0000   1.6000   2.2000
	Result: 1
3:    6.0000   4.0000   4.6000   3.2000
	Result: 3
4:    0.9000   1.0000   2.6000   2.2000
	Result: 1
5:    9.0000   7.0000   4.6000   4.2000
	Result: 3

Test Euclidean:
1:    5.0000   3.0000   1.6000   0.2000
	Result: 1
2:    1.0000   2.0000   1.6000   2.2000
	Result: 2
3:    6.0000   4.0000   4.6000   3.2000
	Result: 3
4:    0.9000   1.0000   2.6000   2.2000
	Result: 2
5:    9.0000   7.0000   4.6000   4.2000
	Result: 3
```

Do you have any suggestions or improves?

Contact me coolerlair [at] gmail [dot] com


