//
// Created by Filip Dabkowski on 11/10/2023.
//
#include "iostream"
#include "cmath"

const char BiulingBlock = '#';
const char fillerBlock = ' ';
using namespace std;

int patternSize;

const int basePattern[6][6] = {
    {0, 1},
    {1, 1},
};

void createFractal(int planeSize, int depth, int y, int x) {
    int relativeY;
    int relativeX;
    int relativePlaneSize = planeSize / patternSize;
    
    if (depth == 1) {
        relativeY = y;
        relativeX = x;
        cout << (basePattern[relativeY % 2][relativeX % 2] ? BiulingBlock : fillerBlock);
    } else {
        relativeY = y / relativePlaneSize;
        relativeX = x / relativePlaneSize;

        if (basePattern[relativeY % 2][relativeX % 2]) {
            createFractal(relativePlaneSize, depth - 1, y - relativePlaneSize * relativeY, x - relativePlaneSize * relativeX );
        } else {
            cout << fillerBlock;
        }
    }
}

int fractals() {

    int recursionLevel;
    cin >> patternSize >> recursionLevel;

    int planeSize = (int) pow((double) patternSize, (double) recursionLevel);
    for (int i = 0; i < planeSize; ++i) {
        for (int j = 0; j < planeSize; ++j) {
            createFractal(planeSize, recursionLevel, i, j);
        }
        cout << endl;
    }

    return 0;
}