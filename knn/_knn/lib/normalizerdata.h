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
