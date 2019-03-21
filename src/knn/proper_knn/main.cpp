#include "knn.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <bits/stdc++.h>
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
		std::string maxClass = knn->getNeighbours(test_data, training, k);
		if (maxClass.compare(test_data.cls) == 0)
		{
			correct++;
		}
	}
	std::cout<<"The total number of correct predictions are: "<<std::endl;
	std::cout <<
		correct << " from the size of test is "<< test.size() <<
		" (" <<
		static_cast<double>(100.0) *correct/static_cast<double>(test.size()) <<
		")" << std::endl;

}


int main(int argc, char **argv)
{
	std::srand(time(nullptr));
	auto dataset = read_iris_data("iris.data");
	std::random_shuffle(dataset.begin(), dataset.end());
	auto splitted_data = split_data(dataset);
	dataset.clear();
	run_knn(splitted_data.second, splitted_data.first, 10);
	return 0;
}
