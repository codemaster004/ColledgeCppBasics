#include "iostream"
#include "string"

using namespace std;

void binaryAddition() {
    int length1, length2, maxLength, diff = 0;
    string bits1, bits2, bitsFinal, temp;

    cin >> length1;
    cin >> bits1;
    if (length1 > 10) {
        for (int i = 0; i < length1 / 10 - 1; i++) {
            cin >> temp;
            bits1 += temp;
        }
    }

    cin >> length2;
    cin >> bits2;
    if (length2 > 10) {
        for (int i = 0; i < length1 / 10 - 1; i++) {
            cin >> temp;
            bits2 += temp;
        }
    }

    // finding the longest value
    if (length2 > length1) {
        maxLength = length2;
        diff = length2 - length1;
    } else if (length2 < length1) {
        maxLength = length1;
        diff = length1 - length2;
    } else {
        maxLength = length2;
    }

    // if one number smaller than the other
    for (int i = 0; i < diff; i++) {
        if (length1 != maxLength) {
            bits1 = " " + bits1;
        } else {
            bits2 = " " + bits2;
        }
    }

    // Calculation for binary Addition
    maxLength--;
    int memory = 0;
    for (int i = maxLength; i >= 0; i--) {
        int calculation = 0;

        if (bits1[i] == '1')
            calculation += 1;
        if (bits2[i] == '1')
            calculation += 1;

        bitsFinal += (char)((calculation + memory) % 2 + 48);
        memory = (calculation + memory) / 2;

        if (i == 0 && memory == 1) {
            bitsFinal += '1';
            maxLength += 1;
        }
    }

    // print in reverse order
    for (int i = maxLength; i >= 0; i--) {
        if (bitsFinal[i] == ' ') {
            continue;
        }
        cout << bitsFinal[i];
    }
}

//int main() {
//    binaryAddition();
//}