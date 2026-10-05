/*
 * sorter.h
 *
 * Declares a template function:
 *    
 *   sorter() : k-way merge sort.
 * 
 * 
 * You may add other functions if you wish, but this template function
 * is the only one that need to be exposed for the testing code.
 * 
 * Authors: C. Painter-Wakefield & Tolga Can
 */

#ifndef _SORTER_H
#define _SORTER_H

#include <limits>
#include <string>
#include <cstddef>
#include <vector>

/***
 * DO NOT put unscoped 'using namespace std;' in header files!
 * Instead put them at the beginning of class or function definitions
 * (as demonstrated below).
 *
 * For more details, see the commentary at the top of
 *   tests/header-sans-using-namespace.h
 * in this project repo.
 */

template <class T>
void sorter(std::vector<T> &items, std::size_t k) {  
	if (items.size() < 2 || k < 2) {
		return; // nothing to sort
	}

	// create k new arrays
	std::vector<std::vector<T>> subarrays(k);

	// reseve space for each subarray, to avoid reallocations
	for (std::vector<T>& subarray : subarrays) {
		// each array will either have `n / k` or `n / k + 1` elements,
		// we will reserve the larger size to avoid reallocations
		// the extra memory should be relatively insignificant
		subarray.reserve(items.size() / k + 1);
	}
	
	// split the items into subarrays
	for (std::size_t i = 0; i < items.size(); i++) {
		subarrays[i % k].push_back(items[i]);
	}
	
	// sort the subarrays
	for (std::vector<T>& subarray : subarrays) {
		sorter(subarray, k);
	}

	// merge the sorted subarrays back into the original array, maximum elements first
	ssize_t sorted_index = items.size() - 1;
	while (sorted_index >= 0) {
		// find the max element from each subarray
		T max = subarrays[0].size() ? subarrays[0].back() : std::numeric_limits<T>::lowest();
		std::size_t max_index = 0;
		for (std::size_t i = 1; i < k; i++) { // we already checked i = 0
			if (subarrays[i].size() && subarrays[i].back() > max) {
				max = subarrays[i].back();
				max_index = i;
			}
		}
		
		// put the max element into the sorted array
		items[sorted_index] = max;
		sorted_index--;

		// remove the element from the subarray
		subarrays[max_index].pop_back();
	}
}
#endif
