#include <iostream>

using namespace std;

void countOccurrences(char *matrix[], int y, int x, char find) {
    int count = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (matrix[i][j] == find) {
                count++;
            }
        }
    }
    cout << count;
}

void findAndReplace(char *matrix[], int y, int x, char find, char replace) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (matrix[i][j] == find) {
                cout << replace;
            } else {
                cout << matrix[i][j];
            }
            cout << " ";
        }
        cout << endl;
    }
}

int easySomething() {

    int mode;
    char find, replacement = '-';
    int x, y;

    // Handle mode input
    cin >> mode >> find;
    if (mode == 1) {
        cin >> replacement;
    }
    cin >> y >> x;

    // Allocate memory for table
    char **primeTable = new char *[y];
    for (int i = 0; i < y; i++) {
        primeTable[i] = new char[x];
    }

    // Handle table input
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            cin >> primeTable[i][j];
        }
    }

    switch (mode) {
        case 0:
            countOccurrences(primeTable, y, x, find);
            break;
        case 1:
            findAndReplace(primeTable, y, x, find, replacement);
            break;
        default:
            cout << "Please provide a recognised mode";
    }

    // Free up allocated memory
    for (int i = 0; i < y; i++) {
        delete[] primeTable[i];
    }
    delete[] primeTable;

    return 0;
}
