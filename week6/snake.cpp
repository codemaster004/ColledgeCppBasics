//
// Created by Filip Dabkowski on 15/11/2023.
//
#include "iostream"

using namespace std;

#define SNAKE '$'
#define SPACE '.'
#define WALL '#'

const int maxSize = 10;
const int maxMoves = 100;

void read_data(char input[maxSize][maxSize], int *const size_y, int *const size_x) {
    cin >> *size_y;
    cin >> *size_x;

    for (int i = 0; i < *size_y; ++i) {
        for (int j = 0; j < *size_x; ++j) {
            cin >> input[i][j];
        }
    }
}

void printTable(char printingTable[maxSize][maxSize], int maxY, int maxX) {
    for (int i = 0; i < maxY; ++i) {
        for (int j = 0; j < maxX; ++j) {
            cout << printingTable[i][j];
        }
        cout << endl;
    }
}

void snake() {
    char inputTable[maxSize][maxSize];
    int sizeY, sizeX;
    read_data(inputTable, &sizeY, &sizeX);
    int headX, headY;
    int tailX, tailY;
    cin >> headY >> headX >> tailY >> tailX;

    int nMoves;
    cin >> nMoves;
    char moves[maxMoves];
    for (int i = 0; i < nMoves; ++i) {
        cin >> moves[i];
    }
    char toRepl[2];

    toRepl[1] = inputTable[headY][headX];
    toRepl[0] = inputTable[tailY][tailX];

    inputTable[headY][headX] = SNAKE;
    inputTable[tailY][tailX] = SNAKE;

    printTable(inputTable, sizeY, sizeX);
    cout << endl;

    for (int i = 0; i < nMoves; ++i) {
        inputTable[tailY][tailX] = toRepl[0];
        toRepl[0] = toRepl[1];
        if (moves[i] == 'N') {
            tailY = headY;
            tailX = headX;
            headY -= 1;
        } else if (moves[i] == 'E') {
            tailX = headX;
            tailY = headY;
            headX += 1;
        } else if (moves[i] == 'S') {
            tailY = headY;
            tailX = headX;
            headY += 1;
        } else if (moves[i] == 'W') {
            tailX = headX;
            tailY = headY;
            headX -= 1;
        }
        toRepl[1] = inputTable[headY][headX];
        inputTable[headY][headX] = SNAKE;

        printTable(inputTable, sizeY, sizeX);
        cout << endl;
//        moves[i]
    }

//    for (int i = 0; i < sizeY; ++i) {
//        for (int j = 0; j < sizeX; ++j) {
//            if (i == headY && j == headX) {
//                cout << SNAKE;
//            } else if (i == tailY && j == tailX) {
//                cout << SNAKE;
//            } else {
//                cout << inputTable[i][j];
//            }
//        }
//        cout << endl;
//    }

}

//int main() {
//    snake();
//    return 0;
//}