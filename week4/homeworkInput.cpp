#include "iostream"

using namespace std;

bool isSublistInList(const char *primaryList, int primaryLength, const char *subList, int subLength);

void weirdInput() {
    char mode;
    cin >> mode;
    if (mode == 'b') {
        const int SIZE = 100;
        char table[SIZE];
        int index = 0;

        int seqLen;
        cin >> seqLen;

        char tempChar;
        cin.get(tempChar);
        while (cin.get(tempChar) && tempChar != '\n' && index < seqLen - 1) {
            table[index++] = tempChar;
        }
        table[index] = '\0';

        for (int i = 0; i < index; i++) {
            cout << table[i];
        }
        cout << endl;
    } else if (mode == 'e') {
        char most_common_char;
        char characters[10];
        int num_of_characters[10];
        int next_Character_Index = 0;
        int numberOfWords;
        cin >> numberOfWords;
        for (int i = 0; i < numberOfWords; i++) {
            char currentChar;
            currentChar = (char) (getchar());
            if (currentChar == ' ' || currentChar == '\n') {
                continue;
            }

            bool character_Previously_Encountered = false;
            for (int n = 0; n < next_Character_Index; n++) {
                if (characters[n] == currentChar) {
                    num_of_characters[n]++;
                    character_Previously_Encountered = true;
                    break;
                }
            }
            if (!character_Previously_Encountered) {
                characters[next_Character_Index] = currentChar;
                num_of_characters[next_Character_Index] = 1;
                next_Character_Index++;
            }
        }
        int maxCharRepetitions = 0;
        int maxCharRepetitionIndex = 0;
        for (int i = 0; i < next_Character_Index; i++) {
            if (maxCharRepetitions < num_of_characters[i]) {
                maxCharRepetitions = num_of_characters[i];
                maxCharRepetitionIndex = i;
            }
        }
        most_common_char = characters[maxCharRepetitionIndex];
        cout << most_common_char;
        cout << endl;
    } else if (mode == 'f') {
        int numberKeySeq;
        cin >> numberKeySeq;

        char keyWords[10][10];
        int wordsLength[10];
        int wordsEntered = 0;
        int index = 0;

        // parse input
        getchar();
        while (wordsEntered < numberKeySeq) {
            keyWords[wordsEntered][index] = (char) (getchar());
            if (keyWords[wordsEntered][index] == ' ') {
                wordsLength[wordsEntered] = index;
                wordsEntered += 1;
                index = 0;
                continue;
            }
            index += 1;
        }
        int numberOfChars;
        cin >> numberOfChars;

        char tempWord[10];
        int tempLen = 0;
        getchar();
        for (int i = 0; i < numberOfChars; ++i) {
            tempWord[tempLen] = (char) (getchar());
            if (tempWord[tempLen] == ' ') {
                bool patternWasFound = false;
                for (int j = 0; j < wordsEntered; ++j) {
                    if (isSublistInList(tempWord, tempLen, keyWords[j], wordsLength[j])) {
                        patternWasFound = true;
                    }
                }
                if (patternWasFound) {
                    for (int k = 0; k < tempLen; ++k) {
                        cout << '*';
                    }
                } else {
                    for (int k = 0; k < tempLen; ++k) {
                        cout << tempWord[k];
                    }
                }
                cout << " ";
                tempLen = 0;
                continue;
            }
            tempLen += 1;
        }
    }
}

bool isSublistInList(const char *primaryList, int primaryLength, const char *subList, int subLength) {
    if (subLength > primaryLength)
        return false;

    bool patterMatched = true;
    for (int j = 0; j <= primaryLength - subLength; ++j) {
        patterMatched = true;
        for (int k = 0; k < subLength; ++k) {
            if (primaryList[j + k] != subList[k]) {
                patterMatched = false;
            }
        }
        if (patterMatched) {
            break;
        }
    }
    return patterMatched;
}


//int main() {
//    weirdInput();
//    return 0;
//}