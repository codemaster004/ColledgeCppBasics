#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

#define PI 3.1415
#define N_SECTORS 8

const int maxNumTrees = 2;

struct Tree {
    bool isActive = false;
    float positionX{};
    float positionY{};
    float crownRadius{};
    float trunkHeight{};
};

int checkSector(float vectorX, float vectorY);

float calcHypotenuse2(float a, float b);

int binaryTableToNumber(const int *binaryMap);

void treeGame() {
    // Allocate memory for Tree data
    auto **trees = new Tree *[maxNumTrees];
    for (int i = 0; i < 2; i++) {
        trees[i] = new Tree;
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
                if (trees[index]->isActive) {
                    cout << "Tree already active" << endl;
                    continue;
                }

                trees[index]->isActive = true; // isActive
                cin >> trees[index]->positionY; // posY
                cin >> trees[index]->positionX; // posX
                cin >> trees[index]->crownRadius; // treeR
                cin >> trees[index]->trunkHeight; // treeH
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
                int x1, x2, y1, y2;
                cin >> x1;
                cin >> x2;
                cin >> y1;
                cin >> y2;

                int nRows = abs(y1) + abs(y2);
                int nCols = abs(x1) + abs(x2);

                // Iterate over the board area
                for (int i = 0; i < nRows; ++i) {
                    for (int j = 0; j < nCols; ++j) {

                        auto checkingX = (float) (j + 0.5 + y1);
                        auto checkingY = (float) (i + 0.5 + x1);

                        bool slotOccupied = false;
                        for (int n = 0; n < maxNumTrees; n++) {
                            float vectorY = checkingY - trees[n]->positionY;
                            float vectorX = checkingX - trees[n]->positionX;

                            if (calcHypotenuse2(vectorY, vectorX) <= trees[n]->crownRadius * trees[n]->crownRadius) {
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

                    cout << (i + 1) << " at " << trees[i]->positionY << ", " << trees[i]->positionX << " r="
                         << trees[i]->crownRadius << " h=" << trees[i]->trunkHeight << endl;
                    if (mode == 2) {
                        cout << " Interfering with: ";

                        int compassEncoder[N_SECTORS];
                        for (int &j: compassEncoder) {
                            j = 0;
                        }

                        for (int j = 0; j < maxNumTrees; j++) {
                            if (i == j)
                                continue;

                            float shiftX = trees[j]->positionX - trees[i]->positionX;
                            float shiftY = trees[j]->positionY - trees[i]->positionY;
                            float sumR = trees[j]->crownRadius + trees[i]->crownRadius;

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
        } else if (command == "ADV") {
            int nEpochs;
            cin >> nEpochs;

            assert(not isnan(r_incr));
            assert(not isnan(h_incr));

            for (int i = 0; i < maxNumTrees; ++i) {
                trees[i]->crownRadius += (float) nEpochs * r_incr;
                trees[i]->trunkHeight += (float) nEpochs * h_incr;
            }
        } else if (command == "END") {
            break;
        } else {
            cout << "Unknown command" << endl;
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
        arcCos = float((float) (PI - arcCos) + PI);
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
