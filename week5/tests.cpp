#include "iostream"

using namespace std;

int a[2][2];

int g(int x[2], int i, int j) {
    x[0] = (i + 2) % 4;
    if (i <= j)
        if (g(x, j, i) <= j)
            x[1] = i + (j++);

    return x[1];
}

int x;

int test2018() {
//    a[1][0] = g(a[0], 2, 3);
//    a[0][1] = g(a[1], 5, 1);

    int tab[3] = {1, 2, 3};
    int *x = tab;
    cout << sizeof(tab) << endl;
    cout << sizeof(x) / sizeof(int) << endl;
    cout << (0 ^ 0) << endl;

//    cout << a[0][0] << " " << a[0][1] << " " << a[1][0] << " " << a[1][1];

    unsigned int u = 0;
    cout << (u + 1) - x[1];

    return 0;
}

void zad4_1() {
    int *p = (int *) malloc(10 * sizeof(int));
    int t[10], g = 4, *b = &(p[7]);
    char s[] = {"Napisy"};
    cout << p << endl;
    // 60 00 03 ff 82 70
    cout << (int) sizeof(p) - (int) sizeof(t) << endl;
    cout << sizeof(s) << endl;
    cout << g + g++ << endl;
    cout << p - b << endl;
}

int addition_example(int *a, int n) {
    if (n > 1) {
        return addition_example(a + 1, n - 1) + (a[0] > a[1] ? 1 : 0);
    } else {
        return 0;
    }
}

//int main() {
//    int stupid_table[] = {3, 5, 8, 4, 6, 3, 3, 9, 6, 3, 7, 6, 1};
//    addition_example(stupid_table, 13);
//
//}