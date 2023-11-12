#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

#define PI 3.1415
#define N_SECTORS 8

const int maxNumTrees = 10;

struct Tree {
    bool isActive = false;
    int id = 0;
    float positionX{};
    float positionY{};
    float crownRadius{};
    float trunkHeight{};
};

int checkSector(float vectorX, float vectorY);

float calcHypotenuse2(float a, float b);

int binaryTableToNumber(const int *binaryMap, int nElements);

bool isWithinDiagonal(float distanceX, float distanceY, float diagonal);

bool doesTreesInterfere(Tree originTree, Tree checkingTree);

int findTreeIndexById(Tree **trees, int treeId);

void advanceForest(Tree **trees, float crownIncrease, float trunkIncrease, int years);

void printCurrentForest(Tree **trees, float minX, float maxX, float minY, float maxY, float precision, int mode);

void printInterferences(Tree **trees, int originalTreeId);

void printSimulationPlant(Tree **trees, Tree checkingTree, int x1, int x2, int y1, int y2);

void treeGame() {
    // Allocate memory for Tree data
    auto **trees = new Tree *[maxNumTrees];
    for (int i = 0; i < maxNumTrees; i++) {
        trees[i] = new Tree;
    }

    float r_incr = 0;
    float h_incr = 0;

    while (true) {
        string command;
        cin >> command;
        if (command == "ADD") {
            // MODE: Add tree to the forest
            int id, index;
            cin >> id;
            index = id;

            if (trees[index] != nullptr) {
                if (trees[index]->isActive) {
                    cout << "Tree already active" << endl;
                    continue;
                }

                trees[index]->isActive = true;
                cin >> trees[index]->positionY >> trees[index]->positionX;
                cin >> trees[index]->crownRadius >> trees[index]->trunkHeight;
            }
        } else if (command == "MDL") {
            // MODE: ?How tree grows?
            int mode;
            cin >> mode;
            if (mode == 0) {
                cin >> r_incr >> h_incr;
            }
        } else if (command == "PRT") {
            // MODE: Print some information about the forest
            int mode;
            cin >> mode;
            if (mode == 3) {
                // Print the current coverage of the forest in a given area
                float x1, x2, y1, y2;
                cin >> x1 >> x2 >> y1 >> y2;

                printCurrentForest(trees, x1, x2, y1, y2, 1, 0);

            } else if (mode == 1 || mode == 2) {
                // Print information about all the trees
                cout << "Trees:" << endl;
                for (int i = 0; i < maxNumTrees; i++) {
                    if (trees[i] == nullptr || !trees[i]->isActive)
                        continue;

                    cout << i << " at " << trees[i]->positionY << ", " << trees[i]->positionX;
                    cout << " r=" << trees[i]->crownRadius << " h=" << trees[i]->trunkHeight << " ";

                    if (mode == 2) {
                        // Also provide information about interference with other trees
                        printInterferences(trees, i);
                    }
                    cout << endl;
                }

            } else if (mode == 4) {
                // Print a simulation of plating a new tree in
                int x1, x2, y1, y2;
                int years;
                cin >> x1 >> x2;
                cin >> y1 >> y2;
                Tree checkingTree = Tree();
                cin >> checkingTree.crownRadius >> checkingTree.trunkHeight >> years;

                // Advance the forest to check environment
                checkingTree.crownRadius += r_incr * (float) (years);
                checkingTree.trunkHeight += h_incr * (float) (years);
                advanceForest(trees, r_incr, h_incr, years);

                printSimulationPlant(trees, checkingTree, x1, x2, y1, y2);

                // return forest to unchanged state
                advanceForest(trees, r_incr, h_incr, -years);
            } else if (mode == 5) {
                int id, gridSize;
                float distanceFromTree;
                cin >> id >> gridSize >> distanceFromTree;

                // TODO: Implement new leaf printing
                Tree centerTree = *trees[findTreeIndexById(trees, id)];
                float minX = centerTree.positionX - distanceFromTree, maxX = centerTree.positionX + distanceFromTree;
                float minY = centerTree.positionY - distanceFromTree, maxY = centerTree.positionY + distanceFromTree;
                printCurrentForest(trees, minX, maxX, minY, maxY, (maxX - minX) / (float) (gridSize), 1);

            }
        } else if (command == "REM") {
            // TODO: remove tree functionality
            int id;
            cin >> id;
        } else if (command == "ADV") {
            int nEpochs;
            cin >> nEpochs;

            assert(not isnan(r_incr));
            assert(not isnan(h_incr));

            advanceForest(trees, r_incr, h_incr, nEpochs);
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

    for (int i = 0; i < N_SECTORS; i++) {
        float angle = prevAngle + (float) (sectorRange / 180.0 * PI);
        if (arcCos >= prevAngle && arcCos <= angle) {
            sector = i;
            break;
        }
        prevAngle = angle;
    }
    return sector;
}

float calcHypotenuse2(float a, float b) {
    return a * a + b * b;
}

int binaryTableToNumber(const int *binaryMap, int nElements) {
    int finalNumber = 0;

    int multiplier = 1;
    for (int i = 0; i < nElements; ++i) {
        finalNumber += binaryMap[i] * multiplier;
        multiplier *= 2;
    }
    return finalNumber;
}

bool isWithinDiagonal(float distanceX, float distanceY, float diagonal) {
    return calcHypotenuse2(distanceX, distanceY) <= diagonal * diagonal;
}

bool doesTreesInterfere(Tree originTree, Tree checkingTree) {
    float shiftX = checkingTree.positionX - originTree.positionX;
    float shiftY = checkingTree.positionY - originTree.positionY;
    float sumR = checkingTree.crownRadius + originTree.crownRadius;

    return isWithinDiagonal(shiftX, shiftY, sumR);
}

void advanceForest(Tree **trees, float crownIncrease, float trunkIncrease, int years) {
    for (int i = 0; i < maxNumTrees; ++i) {
        if (trees[i] == nullptr || !trees[i]->isActive)
            continue;
        trees[i]->crownRadius += (float) years * crownIncrease;
        trees[i]->trunkHeight += (float) years * trunkIncrease;
    }
}

void printCurrentForest(Tree **trees, float minX, float maxX, float minY, float maxY, float precision, int mode) {
    int numStepsY = (int) ((maxY - minY) / precision);
    int numStepsX = (int) ((maxX - minX) / precision);

    // Iterate over the board area
    for (int i = 0; i < numStepsY; ++i) {
        for (int j = 0; j < numStepsX; ++j) {

            auto checkingY = minY + precision * (float) (i) + precision / 2;
            auto checkingX = minX + precision * (float) (j) + precision / 2;

            bool slotOccupied = false;
            for (int n = 0; n < maxNumTrees; n++) {
                float vectorY = checkingY - trees[n]->positionY;
                float vectorX = checkingX - trees[n]->positionX;

                if (isWithinDiagonal(vectorX, vectorY, trees[n]->crownRadius)) {
                    slotOccupied = true;
                }
            }

            cout << (slotOccupied ? "T" : ".");
        }
        cout << endl;
    }
}

// TODO: Those two functions should use callback
void printSimulationPlant(Tree **trees, Tree checkingTree, int x1, int x2, int y1, int y2) {
    int nRows = abs(y1) + abs(y2);
    int nCols = abs(x1) + abs(x2);

    // Iterate over the board area
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            checkingTree.positionX = (float) (x1 + j + 0.5);
            checkingTree.positionY = (float) (y1 + i + 0.5);

            bool collided = false;
            for (int n = 0; n < maxNumTrees; n++) {
                if (collided)
                    break;

                collided = doesTreesInterfere(checkingTree, *trees[n]);
            }
            cout << (collided ? "-" : "+");
        }
        cout << endl;
    }
}

void printInterferences(Tree **trees, int originalTreeId) {
    cout << " Interfering with: ";

    // Create a table for keep sector information
    int compassEncoder[N_SECTORS];
    for (int &j: compassEncoder) {
        j = 0;
    }

    for (int j = 0; j < maxNumTrees; j++) {
        if (trees[j] == nullptr || !trees[j]->isActive)
            continue;
        if (originalTreeId == j)
            continue;

        if (doesTreesInterfere(*trees[originalTreeId], *trees[j])) {
            cout << j << " ";

            float shiftX = trees[j]->positionX - trees[originalTreeId]->positionX;
            float shiftY = trees[j]->positionY - trees[originalTreeId]->positionY;

            int sector = checkSector(shiftX, shiftY);
            if (sector >= 0)
                compassEncoder[sector] = 1;
        }
    }
    cout << " COMPASS: " << binaryTableToNumber(compassEncoder, N_SECTORS);
}

int findTreeIndexById(Tree **trees, int treeId) {
    for (int i = 0; i < maxNumTrees; ++i)
        if (trees[i]->id == treeId)
            return i;

    return -1;
}

int main() {
    treeGame();
    return 0;
}
