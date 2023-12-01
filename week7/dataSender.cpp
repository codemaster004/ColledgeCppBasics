//
// Created by Filip Dabkowski on 25/11/2023.
//
#include <iostream>

using namespace std;

void printTable(int **table, int sizeY, int sizeX) {
	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; ++j) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void fillTable(int **table, int sizeY, int sizeX) {
	for (int i = 0; i < sizeY; ++i) {
		for (int j = 0; j < sizeX; ++j) {
			table[i][j] = 0;
		}
	}
}

//void moveValuesForward(int *table, int len) {
//	for (int i = len - 1; i >= 0; --i) {
//		if (i != 0) {
//			table[i] += table[i - 1];
//			table[i - 1] = 0;
//		}
//	}
//}

int dataSender() {
	int *fileSize = nullptr;
	int numberOfFiles = 0;
	cin >> numberOfFiles;
	fileSize = (int *) malloc(numberOfFiles * sizeof(int));
	for (int i = 0; i < numberOfFiles; i++) {
		cin >> fileSize[i];
	}

	int numberOfPoles;
	cin >> numberOfPoles;

	int *capacity = nullptr;
	int numberOfCapacities = 0;
	cin >> numberOfCapacities;
	capacity = (int *) malloc(numberOfCapacities * sizeof(int));

	for (int i = 0; i < numberOfCapacities; i++) {
		cin >> capacity[i];
	}

	// Reserve memory for visualisation table
	int **transfer = new int *[numberOfFiles];
	for (int i = 0; i < numberOfFiles; ++i) {
		transfer[i] = new int[numberOfPoles + 2];
	}

	int length = numberOfPoles + 2;
	fillTable(transfer, numberOfFiles, length);
	for (int i = 0; i < numberOfFiles; ++i) {
		transfer[i][0] = fileSize[i];
	}
	printTable(transfer, numberOfFiles, length);

	int sendingFileIndex = 0;
	for (int i = 0; i < numberOfCapacities; i++) {
		int bytesToSend = capacity[i];
		for (int j = 0; j < bytesToSend; ++j) {
			if (sendingFileIndex < numberOfFiles && transfer[sendingFileIndex][0]) {
				transfer[sendingFileIndex][1]++;
				transfer[sendingFileIndex][0]--;
			}
			if (sendingFileIndex < numberOfFiles && !transfer[sendingFileIndex][0]) {
				sendingFileIndex++;
			}
		}
		printTable(transfer, numberOfFiles, length);
		for (int j = 0; j < numberOfFiles; ++j) {
//			moveValuesForward(transfer[j] + 1, length - 1);
		}
	}

	// Free up memory
	free(fileSize);
	free(capacity);
	for (int i = 0; i < numberOfFiles; ++i) {
		delete[] transfer[i];
	}
	delete[] transfer;

	return 0;
}

//int main() {
//	dataSender();
//	return 0;
//}