#include "iostream"
#include <cassert>

using namespace std;

int bitOperations() {
    unsigned int number = 231;

    unsigned int a1 = 123;
    unsigned int a2 = 43;
    assert(a1 < 255);
    assert(a2 < 255);
    number = number | (a1 << 24);
    number = number | (a2 << 16);
    bool flag = true;
    if (flag) {
        number = number | (1 << 8);
    }


    for (int i = 0; i < sizeof(number) * 8; i++) {
        unsigned int shiftedNumber = number >> (sizeof(number) * 8 - 1 - i);
        unsigned int bitAtPosition1 = shiftedNumber % 2;
        unsigned int bitAtPosition2 = shiftedNumber & 1;
        assert(bitAtPosition1 == bitAtPosition2);
        cout << bitAtPosition1;
        if (i % 8 == 7) {
            cout << endl;
        } else if (i % 4 == 3) {
            cout << " ";
        }
    }
    cout << endl;
}