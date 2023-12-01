//
// Created by Filip Dabkowski on 29/11/2023.
//


#include <iostream>
#include "assert.h"

#define N_WORKING_HOURS 8

using namespace std;

struct Vector {
	int *numbers;
	size_t reservedSpace;
	size_t numberOfActualElements;
};

void initVector(Vector *v) {
	v->numbers = new int[1];
	v->reservedSpace = 1;
	v->numberOfActualElements = 0;
}

Vector *initVectors(size_t n) {
	Vector *temp = new Vector[n];
	for (size_t i = 0; i < n; i++) {
		initVector(&temp[i]);
	}
	return temp;
}

void freeVector(Vector *v) {
	delete[] v->numbers;
}

void freeVectors(Vector *vectors, size_t n) {
	for (size_t i = 0; i < n; i++) {
		freeVector(&vectors[i]);
	}
}

void expendVector(Vector *v) {
	int *temp = new int[v->reservedSpace * 2];
	for (size_t i = 0; i < v->numberOfActualElements; i++) {
		temp[i] = v->numbers[i];
	}
	delete[] v->numbers;
	v->numbers = temp;
	v->reservedSpace *= 2;
	v->numberOfActualElements = v->numberOfActualElements;
}

void shiftRight(Vector *v) {
	assert(v->reservedSpace > v->numberOfActualElements);
	for (size_t i = v->numberOfActualElements; i > 0; i--) {
		v->numbers[i] = v->numbers[i - 1];
	}
}

void addToFront(Vector *vect, int x) {
	if (vect->numberOfActualElements == vect->reservedSpace) {
		expendVector(vect);
	}
	shiftRight(vect);
	vect->numbers[0] = x;
	vect->numberOfActualElements++;
}

void addToBack(Vector *vect, int x) {
	if (vect->numberOfActualElements == vect->reservedSpace) {
		expendVector(vect);
	}
	vect->numbers[vect->numberOfActualElements] = x;
	vect->numberOfActualElements++;
}

void shiftLeft(Vector *vect) {
	for (size_t i = 0; i < vect->numberOfActualElements - 1; i++) {
		vect->numbers[i] = vect->numbers[i + 1];
	}
}

int popFront(Vector *vect) {
	assert(vect->numberOfActualElements > 0);
	int returnedValue = vect->numbers[0];
	shiftLeft(vect);
	vect->numberOfActualElements--;
	return returnedValue;
}

int popBack(Vector *vect) {
	assert(vect->numberOfActualElements > 0);
	int returnedValue = vect->numbers[vect->numberOfActualElements - 1];
	vect->numberOfActualElements--;
	return returnedValue;
}

void showVector(Vector *v, size_t id) {
	cout << id << ":";
	for (size_t i = 0; i < v->numberOfActualElements; i++) {
		cout << " " << v->numbers[i];
	}
	cout << endl;
}

void simulateWork() {
	int numberOfWorkers;
	cin >> numberOfWorkers;

	int maxBacklog;
	cin >> maxBacklog;

	int nSimulationDays;
	cin >> nSimulationDays;

	auto *jobs = new Vector[numberOfWorkers];

	for (int i = 0; i < numberOfWorkers; ++i) {
		jobs[i] = Vector{};
		initVector(&jobs[i]);
	}

	for (int _ = 0; _ < nSimulationDays; ++_) {
		for (int i = 0; i < numberOfWorkers; ++i) {
			int nJobs;
			cin >> nJobs;
			for (int j = 0; j < nJobs; ++j) {
				int taskLength;
				cin >> taskLength;
				addToBack(&jobs[i], taskLength);
			}
			for (int j = 0; j < N_WORKING_HOURS; ++j) {
				if (!jobs[i].numberOfActualElements)
					continue;
				jobs[i].numbers[0]--;
				if (jobs[i].numbers[0] <= 0)
					popFront(&jobs[i]);
			}
			if (jobs[i].numberOfActualElements >= maxBacklog) {
				cout << "Dean's office is overloaded." << endl;
				for (int j = 0; j < numberOfWorkers; ++j) {
					freeVector(&jobs[j]);
				}
				return;
			}
			showVector(&jobs[i], i);
		}
		cout << endl;
	}
	for (int j = 0; j < numberOfWorkers; ++j) {
		freeVector(&jobs[j]);
	}
}

int main() {
	simulateWork();
}