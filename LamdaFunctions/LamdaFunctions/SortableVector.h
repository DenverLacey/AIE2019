#include <iostream>
#include <algorithm>
#include <vector>

template <class T>
class SortableVector
{
public:
	SortableVector() {}
	SortableVector(std::vector<T> vec) { v = vec; }
	~SortableVector() {}

public:
	T operator [](size_t i) { return v[i]; }

	void PushBack(T e) { v.push_back(e); }
	void PopBack() { v.pop_back(); }

	void PrintElements() {
		for (int i = 0; i < v.size(); i++) {
			std::cout << "[" << v[i] << "]";
		}

		std::cout << "\n";
	}

	int Size() { return v.size(); }

	void Sort(bool(*lf)(T, T) = [](T a, T b) {return a < b; }) { std::sort(v.begin(), v.end(), lf); }

	void InsertionSort(bool(*lf)(T, T) = [](T a, T b) {return a < b; }) {
		for (int i = 1; i < v.size(); i++) {
			int key = v[i];
			int j = i - 1;
			while (j >= 0 && lf(v[j + 1], v[j])) {
				v[j + 1] = v[j];
				v[j] = key;
				j--;
			}
		}
	}

	void BubbleSort(bool(*lf)(T, T) = [](T a, T b) {return a < b; }) {
		for (int i = 0; i < v.size(); i++) {
			for (int j = 1; j < v.size(); j++) {
				if (lf(v[j], v[j - 1])) {
					int temp = v[j - 1];
					v[j - 1] = v[j];
					v[j] = temp;
				}
			}
		}
	}

	void MergeSort(int low, int high, bool(*lf)(T, T) = [](T a, T b) {return a < b; }) {
		T* helper = new T[v.size()];
		MergeSplit(helper, low, high, lf);
		delete helper;
	}

	void QuickSort(int low, int high, bool(*lf)(T, T) = [](T a, T b) {return a < b; }) {
		if (low < high) {
			// pi is partioning index
			int pi = Partition(low, high, lf);

			// separately sort elements before
			// partition and after partition
			QuickSort(low, pi - 1, lf);
			QuickSort(pi + 1, high, lf);
		}
	}

private:
	void MergeSplit(T helper[], int low, int high, bool(*lf)(T, T) = [](T a, T b) {return a < b; }) {
		if (low < high) {
			int middle = (high + low) / 2;
			MergeSplit(helper, low, middle, lf);
			MergeSplit(helper, middle + 1, high, lf);
			Merge(helper, low, middle, high, lf);
		}
	}

	void Merge(T helper[], int low, int middle, int high, bool(*lf)(T, T) = [](T a, T b) {return a < b; }) {
		for (int i = low; i <= high; i++) {
			helper[i] = v[i];
		}

		int left = low;
		int curr = low;
		int right = middle + 1;

		while (left <= middle && right <= high) {
			if (lf(helper[left], helper[right])) {
				v[curr++] = helper[left++];
			}
			else {
				v[curr++] = helper[right++];
			}
		}

		while (left <= middle) {
			v[curr++] = helper[left++];
		}
	}

	/* This function takes last element as pivot, places
	the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
	to left of pivot and all greater elements to right
	of pivot */
	int Partition(int low, int high, bool(*lf)(T, T) = [](T a, T b) {return a < b; }) {
		// pivot
		T pivot = v[high];

		// index of smaller element
		int i = low - 1;

		for (int j = low; j <= high - 1; j++) {
			// if elements should be swapped
			if (lf(v[j], pivot)) {
				// increment index of smaller element
				i++;
				T temp = v[i];
				v[i] = v[j];
				v[j] = temp;
			}
		}
		T temp = v[i + 1];
		v[i + 1] = v[high];
		v[high] = temp;
		return i + 1;
	}

private:
	std::vector<T> v;
};

