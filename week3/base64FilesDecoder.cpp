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

    // Add multiple elements to the array
    void addElements(const char values[], int numElements) {
        unsigned long size = charBytes.size();
        charBytes.resize(size + numElements);
        for (int i = 0; i < numElements; ++i) {
            charBytes[size + i] = values[i];
        }
    }

    unsigned long size() {
        return charBytes.size();
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

    int findIndexOfPattern(const char *pattern, int patternLength) {
        for (int i = 0; i <= charBytes.size() - patternLength; ++i) {
            bool patterMatched = true;
            for (int j = 0; j < patternLength; ++j) {
                if (charBytes[i + j] != pattern[j]) {
                    patterMatched = false;
                }
            }
            if (patterMatched) {
                return i;
            }
        }
        return -1;
    }

    int findIndexOfPatternReverse(const char *pattern, int patternLength) {
        for (unsigned long i = charBytes.size() - patternLength; i > 0; i--) {
            bool patterMatched = true;
            for (int j = 0; j < patternLength; ++j) {
                if (charBytes[i + j - 1] != pattern[j]) {
                    patterMatched = false;
                }
            }
            if (patterMatched) {
                return i - 1;
            }
        }
        return -1;
    }
};

int indexOf(const char *searchTable, char searchElement, int maxElement);

int createBitMask(int numberOfUpBits, int rightOffset);

void printBits(int a);

void inputAndDecodeBase64(DecodedCharHolder *store);

void binaryBrowser(DecodedCharHolder *store);

void readZipFile(DecodedCharHolder *store);

void printInHex(int value, int desiredLength);

void printDecodedAsChars(int *decoded, int length);

void printOutputStructure(int byteIndex, int *bytes, int maxByte);

/// Main Function
void decodeBase64() {
    int mode;
    cin >> mode;
    getchar();

    DecodedCharHolder decodedBytes{};

    inputAndDecodeBase64(&decodedBytes);

    if (mode == 0) {
        binaryBrowser(&decodedBytes);
    } else if (mode == 1) {
        binaryBrowser(&decodedBytes);
        cout << endl;
    }
}

void inputAndDecodeBase64(DecodedCharHolder *store) {
    int encodedNumber = 0;
    int enteredCharCountCheck = 0, paddingCount = 0;

    char tempChar;
    while (cin.get(tempChar) && tempChar != '\n') {
        enteredCharCountCheck++;

        if (tempChar == '=') {
            encodedNumber <<= 6;
            paddingCount++;
        } else {
            encodedNumber <<= 6;
            encodedNumber += indexOf(base64table, tempChar, baseSize);
        }

        if (enteredCharCountCheck == 4) {
            enteredCharCountCheck = 0;

            char decodedBytes[3];
            for (int i = 0; i < 3 - paddingCount; ++i) {

                int mask = createBitMask(8, 8 * (2 - i));
                int decodedNumber = (encodedNumber & mask) >> 8 * (2 - i);

                decodedBytes[i] = (char) (decodedNumber);
            }
            store->addElements(decodedBytes, 3 - paddingCount);
        }
    }
}

int reverseConvertToInt(const vector<char>& bytes) {

    return 0;
}

void readZipFile(DecodedCharHolder *store) {
    char pattern[4] = {80, 75, 5, 6};
    int index = store->findIndexOfPatternReverse(pattern, 4);
    cout << "length: " << store->size() << endl;
    cout << "index: " << index << endl;
    store->getRange(index + 10, 2);

}

void binaryBrowser(DecodedCharHolder *store) {
    unsigned long size = store->size();

    for (int i = 0; i < size / LINE_LENGTH; ++i) {
        vector<char> decodedBytes = store->getRange(LINE_LENGTH * i, LINE_LENGTH * (i + 1));
        int bytes[LINE_LENGTH];
        for (int j = 0; j < LINE_LENGTH; ++j) {
            bytes[j] = (unsigned char) (decodedBytes[j]);
        }
        printOutputStructure(i * LINE_LENGTH, bytes, LINE_LENGTH);
    }

    if (size % LINE_LENGTH != 0) {
        vector<char> decodedBytes = store->getRange(LINE_LENGTH * (size / LINE_LENGTH), (int) (size));
        int bytes[LINE_LENGTH];
        for (int j = 0; j < size % LINE_LENGTH; ++j) {
            bytes[j] = (unsigned char) (decodedBytes[j]);
        }
        printOutputStructure((int) (size), bytes, (int) (size) % LINE_LENGTH);
    }

    printInHex((int) (size), 8);
}

void printOutputStructure(int byteIndex, int *bytes, int maxByte) {
    printInHex(byteIndex, 8);
    cout << "  ";

    for (int i = 0; i < maxByte; ++i) {
        printInHex(bytes[i], 2);
        cout << " ";
    }
    for (int i = 0; i < maxByte - LINE_LENGTH; ++i) {
        cout << "   ";
    }
    cout << " ";
    printDecodedAsChars(bytes, LINE_LENGTH);
    cout << endl;
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

void printDecodedAsChars(int *decoded, int length) {
    cout << '|';
    for (int i = 0; i < length; ++i) {
        cout << (char) (decoded[i] >= 32 && decoded[i] < 127 ? decoded[i] : 46);
    }
    cout << '|';
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