#include "iostream"
#include "string"

using namespace std;

#define LINE_LENGTH 16

const int baseSize = 64;
char base64table[baseSize] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                              'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                              'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '=', '/'};

int indexOf(const char *searchTable, char searchElement, int maxElement);

int createBitMask(int numberOfUpBits, int rightOffset);

void printBits(int a);

void binaryBrowser();

void printInHex(int value, int desiredLength);

void printDecodedChars(int *decoded, int length);

/// Main Function
void decodeBase64() {
    int mode;
    cin >> mode;

    if (mode == 0) {
        getchar();
        binaryBrowser();
    }
}

void binaryBrowser() {
    int encodedNumber = 0;
    int enteredCharsCount = 0, paddingCount = 0, decodedCharsCount = 0;
    int decodedBytes[LINE_LENGTH];

    printInHex(decodedCharsCount, 8);
    cout << "  ";

    char tempChar;
    while (cin.get(tempChar) && tempChar != '\n') {
        enteredCharsCount++;

        if (tempChar == '=') {
            encodedNumber <<= 6;
            paddingCount++;
        } else {
            encodedNumber <<= 6;
            encodedNumber += indexOf(base64table, tempChar, baseSize);
        }

        if (enteredCharsCount % 4 == 0) {
            for (int i = 0; i < 3 - paddingCount; ++i) {

                int mask = createBitMask(8, 8 * (2 - i));
                int decodedNumber = (encodedNumber & mask) >> 8 * (2 - i);
                decodedBytes[decodedCharsCount % 16] = decodedNumber;
                decodedCharsCount++;

                printInHex(decodedNumber, 2);
                cout << ' ';
                if (decodedCharsCount % (int) (0.5 * LINE_LENGTH) == 0)
                    cout << ' ';

                if (decodedCharsCount % LINE_LENGTH == 0) {
                    printDecodedChars(decodedBytes, LINE_LENGTH);
                    printInHex(decodedCharsCount, 8);
                    cout << ' ' << ' ';
                }
            }
        }
    }

    if (decodedCharsCount % LINE_LENGTH != 0) {
        int missingBytes = LINE_LENGTH - decodedCharsCount % LINE_LENGTH;
        for (int i = 1; i <= missingBytes; ++i) {
            cout << ' ' << ' ' << ' ';
            if ((decodedCharsCount + i) % (int) (0.5 * LINE_LENGTH) == 0)
                cout << ' ';
        }

        printDecodedChars(decodedBytes, decodedCharsCount % LINE_LENGTH);
    }
    printInHex(decodedCharsCount, 8);
}

void printInHex(int value, int desiredLength) {
    char decodedValue[desiredLength];
    for (int i = 0; i < desiredLength; ++i) {
        decodedValue[i] = '0';
    }

    int index = desiredLength - 1;
    while (value > 0) {
        int newPart = value % 16;
        decodedValue[index--] = (char) (newPart >= 10 ? newPart + 87 : newPart + 48);
        value /= 16;
    }

    for (int i = 0; i < desiredLength; ++i) {
        cout << decodedValue[i];
    }
}

void printDecodedChars(int *decoded, int length) {
    cout << '|';
    for (int i = 0; i < length; ++i) {
        cout << (char) (decoded[i] >= 32 && decoded[i] < 127 ? decoded[i] : 46);
    }
    cout << '|' << endl;
}

int indexOf(const char *searchTable, char searchElement, int maxElement) {
    for (int i = 0; i < maxElement; ++i) {
        if (searchTable[i] == searchElement) {
            return i;
        }
    }

    return -1;
}

int createBitMask(int numberOfUpBits, int rightOffset) {
    // Other option: ((uint) (-1)) << (32-upBits) >> (32-upBits-offset)
    int result = (1 << numberOfUpBits) - 1;
    result <<= rightOffset;
    return result;
}

void printBits(int a) {
    for (int b = 8 * sizeof(int) - 1; b >= 0; b--) {
        cout << ((a & (1U << b)) > 0);
    }
    cout << endl;
}

//int main() {
//    decodeBase64();
//    return 0;
//}