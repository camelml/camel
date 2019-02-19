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
#include "libfast_knn.h"

// calc matrix distance
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



