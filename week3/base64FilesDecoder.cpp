#include "iostream"

using namespace std;

const int baseSize = 64;
const char base64table[baseSize] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                              'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                              'j','k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '=', '/'};

int indexOf(char searchTable[], char searchElement, int maxElement);

void decodeBase64() {
    int mode;
    cin >> mode;

    string base64data;
    cin >> base64data;

    for (char letter : base64data) {
        indexOf(base64table, letter, baseSize);
    }
}

int indexOf(char searchTable[], char searchElement, int maxElement) {


    return -1;
}

int main() {
    decodeBase64();
    return 0;
}