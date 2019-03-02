#ifndef COLLECT_H
#define COLLECT_H

#include <iostream>
#include <assert.h>
#include <vector>
#include <time.h>
#include <armadillo>
#include <map>
#ifndef NORMALIZERDATA_H
#define NORMALIZERDATA_H

#include <armadillo>
#include <iostream>
using arma::Mat;
using arma::Row;


template <class T> class NormalizerData
{
private:
    Row<T> ranges;
    Row<T> less_values;
    Row<T> max_values;

public:
    Row<T> Brick_limits();
    Row<T> Brick_max_values();
    Row<T> Brick_less_values();

    Mat<T> normalize(Mat<T> table_data);
    Row<T> normalize(Row<T> table_data2);
};

template<class T> Row<T> NormalizerData<T>::Brick_max_values()
{
    return max_values;
}

template<class T> Row<T> NormalizerData<T>::Brick_less_values()
{
    return less_values;
}

template<class T> Row<T> NormalizerData<T>::Brick_limits()
{
    return ranges;
}

template<class T> arma::Row<T> NormalizerData<T>::normalize(arma::Row<T> table_data4)
{
    return (table_data4-less_values)/ranges;
}

template<class T> arma::Mat<T> NormalizerData<T>::normalize(arma::Mat<T> table_data3)
{
    less_values=arma::min(table_data3);
    max_values=arma::max(table_data3);
    ranges=max_values-less_values;
    arma::uword m=table_data3.n_rows;
    arma::Mat<T> norm_table_data=table_data3-repmat(less_values, m, 1);
    norm_table_data=norm_table_data/repmat(ranges, m, 1);

    return norm_table_data;
}

#endif 

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

int FastKNN::Distance()
{
        std::map<uword, int> Counter_of_classes;
        int Maximum_Poll=-1,Maximum_classes=-1,i=0;

        mat distances=repmat(input, DataSet.n_rows,1)-DataSet;

// https://en.wikipedia.org/wiki/Taxicab_geometry
        if(mode_distance.find("manhattan")!=string::npos)
            distances=abs(sum(distances, 1));

// https://en.wikipedia.org/wiki/Euclidean_distance
        if(mode_distance.find("euclidean")!=string::npos)
            distances=sqrt(sum(square(distances),1));

        umat Sorted_indexes=sort_index(distances);

        while(i<k) 
        {
            uword label=labels[Sorted_indexes[i]];

            	if(!Counter_of_classes.count(label))
                	Counter_of_classes.insert(std::make_pair(label, 0));

            Counter_of_classes.at(label)+=1;

            	if(Counter_of_classes.at(label)>Maximum_Poll) 
                {
                	Maximum_Poll=Counter_of_classes.at(label);
                	Maximum_classes=label;
           	    }

            ++i;
        }

        if(Maximum_classes==-1)
        {
            DEBUG_FASTKNN("Error: Max of classes cannot  be negative");
            return 0;
        }

        return Maximum_classes;
}

void FastKNN::train(std::string filepath)
{
// TODO: put labels/classes in argv param
    labels << 1 << endr << 2 << endr << 3 << endr << 4 << endr << 5 << endr;
// TODO: validate file before open...
    data.load(filepath);
    DataSet=data.submat(0, 0, data.n_rows-1, data.n_cols-2);
    DataSet=Normalizer_Data.normalize(DataSet);
    labels=arma::conv_to<ucolvec>::from(data.submat(0, data.n_cols-1, data.n_rows-1, data.n_cols-1));
}

int FastKNN::Classify(std::string type_distance, rowvec input_user, unsigned k_input)
{

    input=Normalizer_Data.normalize(input_user);
    k=k_input;
    mode_distance=type_distance;

    if(DataSet.n_rows!=labels.n_rows)
    {
        DEBUG_FASTKNN("Error: DataSet have diferent size of classes of label input...");
        return 0;
    }

    if(DataSet.n_cols!=input.n_cols)
    {
        DEBUG_FASTKNN("Error: Input need same rows of Dataset");
        return  0;
    }    

    if(!(k_input<=DataSet.n_rows))
    {
        DEBUG_FASTKNN("Error: K value must be less than dataset rows");
        return  0;
    }

    if(type_distance.find("manhattan")!=string::npos||type_distance.find("euclidean")!=string::npos)
        return FastKNN::Distance();	

	return 0;
}