#include "knn.h"
#include <map>
#include <iostream>

std::string Knn::getNeighbours(Data d, std::vector<Data> data_list, size_t k)
{
	double *top_k_distances = new double[k];
	int *top_k_indexes = new int[k];
	std::fill_n(top_k_indexes, k, -1);
	for (size_t index = 0; index < data_list.size(); index++)
	{
		double distance = d.distance(data_list[index]);
		size_t ind = 0;
		while (ind < k && top_k_indexes[ind] != -1 && top_k_distances[ind] < distance)
		{
			ind++;
		}
		if (ind < k)
		{
			int shift_index = k - 1;
			while (shift_index > ind)
			{
				top_k_indexes[shift_index] = top_k_indexes[shift_index - 1];
				top_k_distances[shift_index] = top_k_distances[shift_index - 1];
				shift_index--;
			}
			top_k_indexes[ind] = index;
			top_k_distances[ind] = distance;
		}
	}
	/*
	if (std::rand() % 100 == 0)
	{
		std::cout << "-------------------------------" << std::endl;
		for (size_t i = 0; i < k; i++)
		{
			std::cout << top_k_indexes[i] << ": " << top_k_distances[i] << std::endl;
		}
	}
	 */
	size_t index = 0; 
	std::map<std::string, int> top_k_class_map;
	while (index < k && top_k_indexes[index] != -1)
	{
		top_k_class_map[data_list[top_k_indexes[index]].cls]++;
		index++;
	}
	int max = -1;
	std::string maxClass;
	for (auto pair : top_k_class_map)
	{
		if (pair.second > max)
		{
			max = pair.second;
			maxClass = pair.first;
		}
	}
	return maxClass;
}

