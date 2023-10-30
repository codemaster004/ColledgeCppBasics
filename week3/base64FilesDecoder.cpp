#include "iostream"
#include "vector"

using namespace std;

#define LINE_LENGTH 16

const int baseSize = 64;
char base64table[baseSize] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                              'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                              'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '=', '/'};


class DecodedCharHolder {
private:
    vector<char> charBytes;

public:
    // Add a single element to the array
    void addElement(char value) {
        charBytes.push_back(value);
    }

    // Add multiple elements to the array
    void addElements(char *values[], int numElements) {
        unsigned long size = charBytes.size();
        charBytes.resize(size + numElements);
        for (int i = 0; i < numElements; ++i) {
            charBytes[size + i] = *values[i];
        }
    }

    // Search for an element and return its index (or -1 if not found)
//    int search(int value) {
//
//        return -1; // If not found
//    }

    // Get the element at a specific index (assuming index is valid)
    int get(int index) {
        return charBytes[index];
    }

    // Get range of elements with specified beginning index and length
    vector<char> getRange(int startIndex, int numOfElements) {
        vector<char> requestedBytes;
        requestedBytes.resize(numOfElements);

        for (int i = 0; i < numOfElements; ++i) {
            requestedBytes[i] = charBytes[startIndex + i];
        }

        return requestedBytes;
    }
};

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

//    printInHex(decodedCharsCount, 8);
//    cout << "  ";

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
            char decodedBytesTemp[3];
            for (int i = 0; i < 3 - paddingCount; ++i) {

                int mask = createBitMask(8, 8 * (2 - i));
                int decodedNumber = (encodedNumber & mask) >> 8 * (2 - i);
                decodedBytesTemp[i] = (char) (decodedNumber);
                decodedBytes[decodedCharsCount % LINE_LENGTH] = decodedNumber;
                decodedCharsCount++;

//                printInHex(decodedNumber, 2);
//                cout << ' ';
//                if (decodedCharsCount % (int) (0.5 * LINE_LENGTH) == 0)
//                    cout << ' ';
//
//                if (decodedCharsCount % LINE_LENGTH == 0) {
//                    printDecodedChars(decodedBytes, LINE_LENGTH);
//                    printInHex(decodedCharsCount, 8);
//                    cout << ' ' << ' ';
//                }
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

    if (decodedCharsCount % LINE_LENGTH != 0) {
        printInHex(decodedCharsCount, 8);
    }
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
    return ((1 << numberOfUpBits) - 1) << rightOffset;
}

void printBits(int a) {
    for (int b = 8 * sizeof(int) - 1; b >= 0; b--) {
        cout << ((a & (1U << b)) > 0);
    }
    cout << endl;
}

int main() {
    decodeBase64();
    return 0;
}