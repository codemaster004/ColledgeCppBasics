#include <iostream>

using namespace std;

void moveValuesForward(int *table, int len) {
	for (int i = len - 1; i >= 0; --i) {
		if (i != 0) {
			table[i] += table[i - 1];
			table[i - 1] = 0;
		}
	}
}

int zuziaSender() {

	int f, m, p;
	cin >> f;
	int *nFiles = new int[f];
	for (int i = 0; i < f; i++) {
		cin >> nFiles[i];
	}
	cin >> p;
	cin >> m;
	int *sizes = new int[m];
	for (int i = 0; i < m; i++) {
		cin >> sizes[i];
	}

	int **output = new int *[f];
	for (int i = 0; i < f; i++) {
		output[i] = new int[p + 2]();
	}


	for (int i = 0; i < f; ++i) {
		output[i][0] = nFiles[i];
	}

	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < (p + 2); ++j) {
			cout << output[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < m; i++) {

		for (int j = 0; j < f; j++) {
			moveValuesForward(output[j] + 1, p + 2 - 1);
		}
		for (int j = 0; j < sizes[i]; j++) {
			for (int k = 0; k < f; k++) {
				if (output[k][0] <= 0) {
					continue;
				}
				output[k][0] -= 1;
				output[k][1] += 1;
				break;
			}
		}
		for (int z = 0; z < f; ++z) {
			for (int j = 0; j < (p + 2); ++j) {
				cout << output[z][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	for (int i = 0; i < f; ++i) {
		delete[] output[i];
	}
	delete[] output;
	delete[] sizes;
	delete[] nFiles;

	return 0;
}

//int main() {
//	zuziaSender();
//	return 0;
//}