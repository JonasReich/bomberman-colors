#pragma once
#include <vector>

template<typename T>
bool VectorContains(std::vector<T> _vector, T _searchItem)
{
	if (_vector.size() > 0 == false)
		return false;
	
	for each (T _item in _vector)
		if (_item == _searchItem)
			return true;
	
	return false;
}
