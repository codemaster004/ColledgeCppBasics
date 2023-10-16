#include "iostream"

using namespace std;


void sumRow(int *matrix[], int x, int row) {
    int sum = 0;
    for (int i = 0; i < x; i++) {
        sum += matrix[row][i];
    }

    cout << sum;
}

void sumColumn(int *matrix[], int y, int column) {
    int sum = 0;
    for (int i = 0; i < y; i++) {
        sum += matrix[i][column];
    }

    cout << sum;
}

void sumArray(int *matrix[], int y, int x) {
    int sum = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            sum += matrix[i][j];
        }
    }

    cout << sum;
}

void replaceValue(int *matrix[], int y, int x, int toReplace) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {

            int value = matrix[i][j];
            if (value != toReplace) {
                cout << value;
            } else {
                cout << "-";
            }
            cout << " ";
        }
        cout << endl;
    }
}

int homeworkIntTable() {
    int mode, arg;
    int y, x;

    cin >> mode >> arg;
    cin >> x >> y;

    // Allocate memory for the table
    int **primeTable = new int *[y];
    for (int i = 0; i < y; i++) {
        primeTable[i] = new int[x];
    }

    // Input data
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            cin >> primeTable[i][j];
        }
    }

    // Check mode
    if (mode == 0) {
        sumArray(primeTable, y, x);
    } else if (mode == 1) {
        sumRow(primeTable, x, arg);
    } else if (mode == 2) {
        sumColumn(primeTable, y, arg);
    } else if (mode == 3) {
        replaceValue(primeTable, y, x, arg);
    }

    // Free the allocated memory
    for (int i = 0; i < y; i++) {
        delete[] primeTable[i];
    }
    delete[] primeTable;

    return 0;
}

int homeworkStupid() {
    int mode, arg;
    int y, x;

    cin >> mode >> arg;
    cin >> x >> y;

    int sum = 0;
    int temp;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            cin >> temp;

            if (mode == 0) {
                sum += temp;
            } else if (mode == 1 && i == arg) {
                sum += temp;
            } else if (mode == 2 && j == arg) {
                sum += temp;
            } else if (mode == 3) {
                if (temp == arg) {
                    cout << "-";
                } else {
                    cout << temp;
                }
                cout << " ";
            }
        }
        if (mode == 3) {
            cout << endl;
        }
    }

    if (mode != 3) {
        cout << sum;
    }

    return 0;
}
