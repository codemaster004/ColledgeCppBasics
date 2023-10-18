#include "iostream"

using namespace std;

#define SIZE 3

long long int factorial(int);

void symmetricMatrix() {
    int i, j, symmetric, array[SIZE][SIZE];

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            cin >> array[i][j];
        }
    }

    for (symmetric = 1, i = 1; i < SIZE; i++) {
        for (j = 0; j < i; j++) {
            if (array[i][j] != array[j][i])
                symmetric = 0;
        }
    }

    cout << "This array is " << (symmetric ? "" : "not ") << "symmetric" << endl;
}

// NOTE: an overflow occurs iven for small numbers
long long int factorial(int num) {
    long long int res = 1;
    for (int i = 2; i <= num; i++) {
        res *= i;
    }

    return res;
}

void binomialCoefficient() {
    int n, k;
    cin >> n;
    cin >> k;
    cout << factorial(n) / (factorial(k) * factorial(n-k));
}

int main() {
    binomialCoefficient();
    return 0;
}
/* Try writing a program to compute `e^x`
 * e^x ~= sum([ x^n / n! ] for n in range(inf)) */