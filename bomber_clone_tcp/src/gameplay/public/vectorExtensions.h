#pragma once

#include <vector>
#include <algorithm>

template<typename T>
bool VectorContains(std::vector<T> _vector, T _searchItem)
{
	return (std::find(_vector.begin(), _vector.end(), _searchItem) != _vector.end());
}
