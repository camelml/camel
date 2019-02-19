
#ifndef COLLECT_H
#define COLLECT_H

#include <iostream>
#include <assert.h>
#include <vector>
#include <time.h>
#include <armadillo>
#include <map>
#include "normalizerdata.h"

#define DEBUG_FASTKNN(x, s...) do { \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "\n--- DEBUG-START ---\n\n %.*s %s[%d] %s(): \n", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
 fprintf(stderr,"\n\n--- DEBUG-END ---\n"); \
} while (0);
 
struct MemoryStruct {
  char *memory;
  size_t size;
};

using namespace::std;
using arma::Row;
using arma::Mat;
using arma::endr;
using arma::colvec;
using arma::rowvec;
using arma::ucolvec;
using arma::mat;
using arma::umat;
using arma::uword;

class FastKNN
{
public:
    vector<double> input_vec;
    NormalizerData <double> Normalizer_Data;
    std::string mode_distance;
    mat DataSet, data;
    ucolvec labels;
    rowvec input; 
    int k;
	void train(std::string filepath);
    int Distance();
	int Classify(std::string type_distance, rowvec input_user, unsigned k_input);
};

#endif 