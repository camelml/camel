#include "knn.h"
#include "knn.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <bits/stdc++.h>

std::string Knn::getNeighbours(Data d, std::vector<Data> data_list, size_t k)
{
	double *distances_of_top_k_elements = new double[k];
	int *indexes_of_top_k_elements = new int[k];
	std::fill_n(indexes_of_top_k_elements, k, -1);
	for (size_t index = 0; index < data_list.size(); index++)
	{
		double distance = d.distance(data_list[index]);
		size_t idx = 0;
		while (idx < k && indexes_of_top_k_elements[idx] != -1 && distances_of_top_k_elements[idx] < distance)
		{
			idx++;
		}
		if (idx < k)
		{
			int shift_index_by_1 = k - 1;
			while (shift_index_by_1 > idx)
			{
				indexes_of_top_k_elements[shift_index_by_1] = indexes_of_top_k_elements[shift_index_by_1 - 1];
				distances_of_top_k_elements[shift_index_by_1] = distances_of_top_k_elements[shift_index_by_1 - 1];
				shift_index_by_1--;
			}
			indexes_of_top_k_elements[idx] = index;
			distances_of_top_k_elements[idx] = distance;
		}
	}
    std::cout << " The most nearest neighbors are : " << std::endl;
    for (size_t i = 0; i < k; i++)
    {
        std::cout << indexes_of_top_k_elements[i] << ": " << distances_of_top_k_elements[i] << std::endl;
    }
	size_t index = 0;
	std::map<std::string, int> map_of_top_k_matching;
	while (index < k && indexes_of_top_k_elements[index] != -1)
	{
		map_of_top_k_matching[data_list[indexes_of_top_k_elements[index]].cls]++;
		index++;
	}
	int max = -1;
	std::string maxClass;
	for (auto pair : map_of_top_k_matching)
	{
		if (pair.second > max)
		{
			max = pair.second;
			maxClass = pair.first;
		}
	}
	return maxClass;
}
std::vector<Data> read_iris_data(const std::string &path)
{
	std::vector<Data> data;
	std::ifstream input(path);
	std::string line;
	while(std::getline(input, line))
	{
		std::stringstream test(line);
		std::string segment;
		std::vector<std::string> seglist;

		double *fields = new double[10];
		Data d;
		d.fields = fields;
		d.size = 4;
		int index = 0;
		while (std::getline(test, segment, ','))
		{
			if (index == d.size)
			{
				d.cls = segment;
				break;
			}

			fields[index] = std::stod(segment);
			index++;
		}
		data.push_back(d);
	}
	return data;
}

std::pair<std::vector<Data>, std::vector<Data>> split_data(std::vector<Data> data)
{
	std::vector<Data> training;
	std::vector<Data> test;
	size_t percentage70 = data.size() * 0.7;
	size_t index = 0;
	while (index < percentage70)
	{
		training.push_back(data[index]);
		index++;
	}
	while (index < data.size())
	{
		test.push_back(data[index]);
		index++;
	}
	return std::make_pair(training, test);
}

void run_knn(std::vector<Data> test, std::vector<Data> training, size_t k)
{
	Knn *knn = new Knn();
	size_t correct = 0;
	for (auto test_data : test)
	{
		std::string maxClass = getNeighbours(test_data, training, k);
		if (maxClass.compare(test_data.cls) == 0)
		{
			correct++;
		}
	}
	std::cout<<"OUTPUT: "<<std::endl;
	std::cout<<"The total number of correct predictions are: "<<std::endl;
	std::cout <<
		correct << " from the size of test "<< test.size() <<" is "<<
		" (" <<static_cast<double>(100.0) *correct/static_cast<double>(test.size()) <<")" << std::endl;

}


int main(int argc, char **argv)
{
    std::cout<<"Input for prediction is from the IRIS dataset "<<std::endl;
	std::srand(time(nullptr));
	auto dataset = read_iris_data("iris.data");
	std::random_shuffle(dataset.begin(), dataset.end());
	auto splitted_data = split_data(dataset);
	dataset.clear();
	run_knn(splitted_data.second, splitted_data.first, 10);
	return 0;
}
