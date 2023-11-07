#include "iostream"

using namespace std;

const int MAX = 10;

void writeData(const char data[MAX][MAX], int sizeY, int sizeX) {
    for (int row = 0; row < sizeY; row++) {
        for (int column = 0; column < sizeX; column++) {
            cout << data[row][column];
        }
        cout << endl;
    }
    cout << endl;
}

char neighbours(int polozenieY, int polozenieX, const char board[MAX][MAX], int y, int x) {
    int zmienna = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int locationX = polozenieX + i;
            int locationY = polozenieY + j;
            if (locationX >= 0 and locationX < x and locationY >= 0 and locationY < y) {
                if (board[locationY][locationX] == '1' and !(locationX == polozenieX and locationY == polozenieY))
                    zmienna++;
            }
        }
    }
    return 48 + zmienna;

}

int lifeGame() {
    int x, y;
    cin >> x >> y;
    char board[MAX][MAX];
    char result[MAX][MAX];

    for (int row = 0; row < y; row++) {
        for (int column = 0; column < x; column++) {
            cin >> board[row][column];
        }
    }

    int mode;
    int argument;

    cin >> mode;
    if (mode != 0) {
        cin >> argument;
    }

    if (mode == 0) {
        for (int row = 0; row < y; row++) {
            for (int column = 0; column < x; column++) {
                result[row][column] = neighbours(row, column, board, y, x);
            }
        }
        writeData(result, y, x);
    }


    if (mode == 1) {
        for (int number = 0; number <= argument; number++) {
            writeData(board, y, x);
            for (int row = 0; row < y; row++) {
                for (int column = 0; column < x; column++) {
                    result[row][column] = neighbours(row, column, board, y, x);
                }
            }
            char tempBoard[MAX][MAX];
//            writeData(result, y, x);

            for (int row = 0; row < y; row++) {
                for (int column = 0; column < x; column++) {
                    if (board[row][column] == '0') {
                        if (result[row][column] == '3') {
                            tempBoard[row][column] = '1';
                        } else tempBoard[row][column] = '0';

                    } else if (board[row][column] == '1') {
                        if (not(result[row][column] == '2' or result[row][column] == '3')) {
                            tempBoard[row][column] = '0';
                        } else tempBoard[row][column] = '1';

                    } else tempBoard[row][column] = board[row][column];
                }
            }
            for (int row = 0; row < y; row++) {
                for (int column = 0; column < x; column++) {
                    board[row][column] = tempBoard[row][column];
                }
            }
        }
    }
}

//int main() {
//    lifeGame();
//    return 0;
//}