#include "knn.h"
#include <map>
#include <iostream>

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

