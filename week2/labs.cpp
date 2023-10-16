#include "iostream"

using namespace std;


int basicReplacements() {
    int mode;
    cin >> mode;

    char argument;
    cin >> argument;

    int nSequences;
    cin >> nSequences;

    for (int i = 0; i < nSequences; i++) {
        int seqLength;
        cin >> seqLength;

        if (mode == 0) {

            int sum = 0;
            for (int j = 0; j < seqLength; j++) {
                char tempLetter;
                cin >> tempLetter;
                if (tempLetter == argument) {
                    sum++;
                }
            }

            cout << sum << endl;
        } else if (mode == 1) {

            bool letterEntered = false;
            for (int j = 0; j < seqLength; j++) {
                char tempLetter;
                cin >> tempLetter;

                if (tempLetter == argument) {
                    letterEntered = true;
                }
                if (not letterEntered) {
                    cout << tempLetter;
                }
            }

            cout << endl;
        } else if (mode == 2) {

            bool maySkipNext = false;
            for (int j = 0; j < seqLength; j++) {
                char tempLetter;
                cin >> tempLetter;
                if (not(maySkipNext && tempLetter == argument)) {
                    cout << tempLetter;
                }
                maySkipNext = tempLetter == argument;
            }

            cout << endl;
        }
    }
}