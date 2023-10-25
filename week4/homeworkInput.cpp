#include "iostream"

using namespace std;

void weirdInput() {
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
}


int main() {
    weirdInput();
    return 0;
}