////
//// Created by Filip Dabkowski on 15/11/2023.
////
//#include "iostream"
//
//using namespace std;
//
//const int max_size = 10;
//
//void read_data(char input[max_size][max_size], int *const size_y, int *const size_x) {
//    cin >> *size_y;
//    cin >> *size_x;
//
//    for (int i = 0; i < *size_y; ++i) {
//        for (int j = 0; j < *size_x; ++j) {
//            cin >> input[i][j];
//        }
//    }
//}
//
//char getCharYX(char check_table[max_size][max_size], const int y, const int x, const int size_y, const int size_x) {
//    if (y < size_y and x < size_x)
//        return check_table[y][x];
//    return '\0';
//}
//
//bool isBorderColumn(int x, int sizeX) {
//    return x == 0 || x == sizeX - 1;
//}
//
//bool isBorderRow(int y, int sizeY) {
//    return y == 0 || y == sizeY - 1;
//}
//
//bool isBorderCorner(int y, int x, int sizeY, int sizeX) {
//    return isBorderColumn(x, sizeX) && isBorderRow(y, sizeY);
//}
//
//void printLogin() {
//
//}
//
//void labs6() {
//    char input_table[max_size][max_size];
//    int size_y, size_x;
//    read_data(input_table, &size_y, &size_x);
//
//    for (int i = 0; i < size_y; ++i) {
//        for (int j = 0; j < size_x; ++j) {
////            cout << input_table[i][j];
//            if (input_table[i][j] != '*') {
//                cout << '.';
//                continue;
//            }
////            cout << getCharYX(input_table, i, j, size_y, size_x);
//            int isVertical = 0;
//            isVertical += getCharYX(input_table, i + 1, j, size_y, size_x) == '*' ? 1 : 0;
//            isVertical += getCharYX(input_table, i - 1, j, size_y, size_x) == '*' ? 1 : 0;
//            int isHorizontal = 0;
//            isHorizontal += getCharYX(input_table, i, j + 1, size_y, size_x) == '*' ? 1 : 0;
//            isHorizontal += getCharYX(input_table, i, j - 1, size_y, size_x) == '*' ? 1 : 0;
//
//            if (isHorizontal == isVertical && isHorizontal == 2) {
//                cout << '+';
//            } else if (isHorizontal) {
//                cout << '-';
//            } else if (isVertical) {
//                cout << '|';
//            } else {
//                cout << '?';
//            }
//
//        }
//        cout << endl;
//    }
//}
//
////int main() {
////    labs6();
////    return 0;
////}