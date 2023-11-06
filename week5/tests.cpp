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
    cout << (0 ^ 0);

//    cout << a[0][0] << " " << a[0][1] << " " << a[1][0] << " " << a[1][1];

    return 0;
}

int main() {
    test2018();
}