#include "iostream"

using namespace std;

const int maxNumberOfLetters = 10;

void wordMeasures() {
    int wordLength, mode;
    cin >> wordLength;
    cin >> mode;

    if (mode == 0) {
        int numOfLetters;
        cin >> numOfLetters;

        char letters[maxNumberOfLetters];
        int letterCount[maxNumberOfLetters];
        for (int i = 0; i < numOfLetters; ++i) {
            cin >> letters[i];
            letterCount[i] = 0;
        }

        int numberOfWords;
        cin >> numberOfWords;
        for (int i = 0; i < numberOfWords * wordLength; ++i) {
            char tempLetter;
            cin >> tempLetter;
            for (int j = 0; j < numOfLetters; ++j) {
                if (tempLetter == letters[j])
                    letterCount[j] += 1;
            }
        }

        for (int i = 0; i < numOfLetters; ++i) {
            cout << letters[i] << " " << letterCount[i] << endl;
        }
        return;
    } else if (mode == 1) {
        char keyWordMask[maxNumberOfLetters];
        for (int i = 0; i < wordLength; ++i) {
            cin >> keyWordMask[i];
        }

        int numberOfWords;
        cin >> numberOfWords;

        for (int i = 0; i < numberOfWords; ++i) {
            bool flag = true;
            char currentWord[maxNumberOfLetters];
            for (int j = 0; j < wordLength; ++j) {
                cin >> currentWord[j];
                if(currentWord[j] != keyWordMask[j]) {
                    flag = false;
                }
            }

            if (flag) {
                for (int j = 0; j < wordLength; ++j) {
                    cout << '*';
                }
            } else {
                for (int j = 0; j < wordLength; ++j) {
                    cout << currentWord[j];
                }
            }
            cout << " ";
        }
    } else if (mode == 2) {
        int keyWordLength;
        cin >> keyWordLength;

        char keyWord[maxNumberOfLetters];
        char keyReplace[maxNumberOfLetters];

        for (int i = 0; i < keyWordLength; ++i) {
            cin >> keyWord[i];
        }
        for (int i = 0; i < wordLength; ++i) {
            cin >> keyReplace[i];
        }

        int numberOfWords;
        cin >> numberOfWords;
        for (int i = 0; i < numberOfWords; ++i) {
            char tempWord[maxNumberOfLetters];
            for (int j = 0; j <wordLength; ++j) {
                cin >> tempWord[j];
            }
            bool flag = true;
            for (int j = 0; j <= wordLength - keyWordLength; ++j) {
                flag = true;
                for (int k = 0; k < keyWordLength; ++k) {
                    if (tempWord[j+k] != keyWord[k]) {
                        flag = false;
                    }
                }
                if (flag) {
                    break;
                }
            }
            if (!flag) {
                for (int k = 0; k < wordLength; ++k) {
                    cout << tempWord[k];
                }
            } else {
                for (int k = 0; k < wordLength; ++k) {
                    cout << keyReplace[k];
                }
            }
            cout << " ";
        }
    }
}

//int main() {
//    wordMeasures();
//    return 0;
//}