#include "iostream"
#include "string"

using namespace std;

void sequences() {
    int numSequences;
    string sequenceTypes[3];

    cin >> numSequences;
    for (int i = 0; i < numSequences; i++) {
        string tempSeq;
        char tempSymbol;
        bool wasLetter = false, wasNumber = false;
        for (int j = 0; j < 5; j++) {
            cin >> tempSymbol;
            tempSeq += tempSymbol;
            if ((int)tempSymbol >= 65) {
                wasLetter = true;
            } else {
                wasNumber = true;
            }
        }
        if (wasLetter && wasNumber) {
            sequenceTypes[2] += tempSeq + ' ';
        } else if (wasNumber) {
            sequenceTypes[1] += tempSeq + ' ';
        } else if (wasLetter) {
            sequenceTypes[0] += tempSeq + ' ';
        }
    }
    cout << "WORDS: " << sequenceTypes[0] << endl;
    cout << "NUMBERS: " << sequenceTypes[1] << endl;
    cout << "MIXED: " << sequenceTypes[2] << endl;
}

//int main() {
//    sequences();
//    return 0;
//}