#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>
#include <random>
#include <ctime>

#include "myTime.h"
#include "SortableVector.h"

using std::cout;
using std::vector;


void PrintTimes(const vector<myTime*> times) {
	for (myTime* t : times) {
		cout << "Time Elapsed (" << t->name << "): " << t->time << "ns.\n";
	}
}

void FindWinner(vector<myTime*> entries) {

	myTime small = *entries[0];

	for (int i = 1; i < entries.size(); i++) {
		if (small.time > entries[i]->time) {
			small = *entries[i];
		}
	}

	cout << small.name << " was the fastest at " << small.time << "ns.\n";
}

vector<int> InitialiseRandomVectorOfSize(int size) {
	vector<int> vec;
	for (int i = 0; i < size; i++) {
		vec.push_back(i + 1);
	}
	std::random_shuffle(vec.begin(), vec.end());
	return vec;
}

int main() {
	// log memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand((unsigned)time(0));

	vector<int> randomisedVec = InitialiseRandomVectorOfSize(10);
	auto lf_compare = [](int a, int b) { return a < b; };

	SortableVector<int> insertionSV(randomisedVec);
	SortableVector<int> bubbleSV(randomisedVec);
	SortableVector<int> mergeSV(randomisedVec);
	SortableVector<int> quickSV(randomisedVec);
	SortableVector<int> algorithmSV(randomisedVec);

	// insertion sort
	auto t1 = std::chrono::steady_clock::now();
	insertionSV.InsertionSort(lf_compare);
	auto t2 = std::chrono::steady_clock::now();
	// insertionSV.PrintElements();

	// bubble sort
	auto t3 = std::chrono::steady_clock::now();
	bubbleSV.BubbleSort(lf_compare);
	auto t4 = std::chrono::steady_clock::now();
	// bubbleSV.PrintElements();

	// merge sort
	auto t5 = std::chrono::steady_clock::now();
	mergeSV.MergeSort(0, mergeSV.Size() - 1, lf_compare);
	auto t6 = std::chrono::steady_clock::now();
	// mergeSV.PrintElements();

	// quick sort
	auto t7 = std::chrono::steady_clock::now();
	quickSV.QuickSort(0, quickSV.Size() - 1, lf_compare);
	auto t8 = std::chrono::steady_clock::now();
	// quickSV.PrintElements();

	// algorithm sort
	auto t9 = std::chrono::steady_clock::now();
	algorithmSV.Sort(lf_compare);
	auto t10 = std::chrono::steady_clock::now();
	// algorithmSV.PrintElements();

	cout << "No. of elements: " << randomisedVec.size() << "\n";

	vector<myTime*> times;

	times.push_back(new myTime(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count(), (char*)"Insertion Sort"));
	times.push_back(new myTime(std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count(), (char*)"Bubble Sort"));
	times.push_back(new myTime(std::chrono::duration_cast<std::chrono::nanoseconds>(t6 - t5).count(), (char*)"Merge Sort"));
	times.push_back(new myTime(std::chrono::duration_cast<std::chrono::nanoseconds>(t8 - t7).count(), (char*)"Quick Sort"));
	times.push_back(new myTime(std::chrono::duration_cast<std::chrono::nanoseconds>(t10 - t9).count(), (char*)"Algorithm Sort"));

	PrintTimes(times);
	FindWinner(times);

	// delete all times
	for (myTime* t : times) {
		if (t != nullptr) {
			delete t;
		}
	}
	times.clear();
}
