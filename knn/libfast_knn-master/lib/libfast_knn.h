/*
#    Copyright (C) 2017 libfast_knn authors(Antonio Costa, Cooler_),
#    
#    This file is part of libfast_knn
#    
#    libfast_knn is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    libfast_knn is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#    You should have received a copy of the GNU Lesser General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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