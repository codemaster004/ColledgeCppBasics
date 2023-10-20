#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

#define PI 3.1415
#define N_SECTORS 8

const int maxNumTrees = 2;

int checkSector(float vectorX, float vectorY);

float calcHypotenuse2(float a, float b);

int binaryTableToNumber(const int *binaryMap);

void treeGame() {
    // Allocate memory for Tree data
    auto **trees = new float *[maxNumTrees];
    for (int i = 0; i < 2; i++) {
        trees[i] = new float[5];
    }

    float r_incr;
    float h_incr;

    while (true) {
        string command;
        cin >> command;
        if (command == "ADD") {
            int id, index;
            cin >> id;
            index = id - 1;

            if (trees[index] != nullptr) {
                if (trees[index][0] == 1) {
                    cout << "Tree already active" << endl;
                    continue;
                }

                trees[index][0] = 1; // isActive
                cin >> trees[index][1]; // posY
                cin >> trees[index][2]; // posX
                cin >> trees[index][3]; // treeR
                cin >> trees[index][4]; // treeH
            }
        } else if (command == "MDL") {
            int mode;
            cin >> mode;
            if (mode == 0) {
                cin >> r_incr;
                cin >> h_incr;
            }
        } else if (command == "PRT") {
            int mode;
            cin >> mode;
            if (mode == 3) {
                /* Print the status of the board in the area [x1, x2] x [y1, y2] in the following way.
                 * Divide the board into squares of size 1 x 1.
                 * If a center of a given square is inside a living tree and the desired rectangle, print T letter.
                 * Otherwise, print .
                 * */
                int x1, x2, y1, y2;
                cin >> x1;
                cin >> x2;
                cin >> y1;
                cin >> y2;
                // TODO: some visualisation
                int nRows = abs(y1) + abs(y2);
                int nCols = abs(x1) + abs(x2);

                // Iterate over the board area
                for (int i = 0; i < nRows; ++i) {
                    for (int j = 0; j < nCols; ++j) {

                        auto checkingX = (float)(j + 0.5 + y1);
                        auto checkingY = (float)(i + 0.5 + x1);

                        bool slotOccupied = false;
                        for (int n = 0; n < maxNumTrees; n++) {
                            float vectorY = checkingY - trees[n][1];
                            float vectorX = checkingX - trees[n][2];

                            if (calcHypotenuse2(vectorY, vectorX) <= trees[n][3] * trees[n][3]) {
                                slotOccupied = true;
                            }
                        }

                        cout << (slotOccupied ? "T" : ".");
                    }
                    cout << endl;
                }

            } else if (mode == 1 || mode == 2) {
                cout << "Trees:" << endl;
                for (int i = 0; i < maxNumTrees; i++) {
                    if (trees[i] == nullptr)
                        continue;

                    cout << (i + 1) << " at " << trees[i][1] << ", " << trees[i][2] << " r=" << trees[i][3] << " h="
                         << trees[i][4] << endl;
                    if (mode == 2) {
                        cout << " Interfering with: ";

                        int compassEncoder[N_SECTORS];
                        for (int &j: compassEncoder) {
                            j = 0;
                        }

                        for (int j = 0; j < maxNumTrees; j++) {
                            if (i == j)
                                continue;

                            float shiftX = trees[j][2] - trees[i][2];
                            float shiftY = trees[j][1] - trees[i][1];
                            float sumR = trees[j][3] + trees[i][3];

                            if (calcHypotenuse2(shiftX, shiftY) <= sumR * sumR) {
                                cout << j + 1 << endl;

                                int sector = checkSector(shiftX, shiftY);
                                compassEncoder[sector] = 1;
                            }
                        }
                        cout << " COMPASS: " << binaryTableToNumber(compassEncoder) << endl;
                    }
                }

            }
        } else if (command == "REM") {
            int id;
            cin >> id;
            if (id == 1) {
//                t1active = false;
            } else if (id == 2) {
//                t2active = false;
            }
        } else if (command == "ADV") {
            int nEpochs;
            cin >> nEpochs;

            assert(not isnan(r_incr));
            assert(not isnan(h_incr));

            for (int i = 0; i < maxNumTrees; ++i) {
                trees[i][3] += (float) nEpochs * r_incr;
                trees[i][4] += (float) nEpochs * h_incr;
            }
        } else if (command == "END") {
            break;
        } else {
            cout << "Unknow command" << endl;
        }
    }

    // Free up the memory
    for (int i = 0; i < maxNumTrees; i++) {
        delete[] trees[i];
    }
    delete[] trees;
}

int checkSector(float vectorX, float vectorY) {
    int sector = -1;
    float r = sqrt(calcHypotenuse2(vectorX, vectorY));
    float numAngle = vectorY / r;

    float arcCos = acos(numAngle);
    if (vectorX < 0) {
        arcCos = float((float)(PI - arcCos) + PI);
    }

    float sectorRange = 360.0 / N_SECTORS;
    float prevAngle = sectorRange / (float) (-2.0) / (float) (180.0) * float(PI);

    for (int i = 0; i < 8; i++) {
        float angle = prevAngle + (float) (sectorRange / 180.0 * PI);
        if (arcCos >= prevAngle && arcCos <= angle) {
            sector = i;
            break;
        }
        prevAngle = angle;
    }
    assert(sector >= 0 && sector <= 7);
    return sector;
}

float calcHypotenuse2(float a, float b) {
    return a * a + b * b;
}

int binaryTableToNumber(const int *binaryMap) {
    int finalNumber = 0;

    int multiplier = 1;
    for (int i = 0; i < N_SECTORS; ++i) {
        finalNumber += binaryMap[i] * multiplier;
        multiplier *= 2;
    }
    return finalNumber;
}

int main() {
    treeGame();
    return 0;
}
