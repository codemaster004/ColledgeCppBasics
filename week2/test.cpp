#include "iostream"
#include "string"

using namespace std;


int easyLabs() {
    int mode;
    string argument;

    cin >> mode;
    if (mode == 1 || mode == 2) {
        cin >> argument;
    }

    int sum = 0;

    int nLists;
    cin >> nLists;

    for (int i = 0; i < nLists; i++) {
        int listLength;
        cin >> listLength;

        for (int j = 0; j < listLength; j++) {
            string tempProduct;
            int tempPrice;

            cin >> tempProduct;
            cin >> tempPrice;

            switch (mode) {
                case 1:
                    if (tempProduct == argument) {
                        sum += tempPrice;
                    }
                    break;
                case 2:
                    if (tempProduct == argument) {
                        sum++;
                    }
                    break;
                default:
                    sum += tempPrice;
            }
        }
    }

    cout << sum;

    return 0;
}

void printInBit(int a) {
    for (int b= 8 * sizeof(int) - 1; b >= 0; b--) {
        cout << ((a & (1U << b)) > 0);
    }
    cout << endl;
}
