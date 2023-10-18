#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

#define PI 3.1415

const int maxNumTrees = 2;

float calcHypotenuse2(float a, float b) {
    return a * a + b * b;
}

void treeGame() {
    float **trees = new float *[maxNumTrees];
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
                cin >> r_incr >> h_incr;
                // TODO: Simulation
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
            } else if (mode == 1 || mode == 2) {
                cout << "Trees:" << endl;
                for (int i = 0; i < maxNumTrees; ++i) {
                    if (trees[i] == nullptr)
                        continue;

                    cout << (i + 1) << " at " << trees[i][1] << ", " << trees[i][2] << " r=" << trees[i][3] << " h=" << trees[i][4] << endl;
                }
//                cout << "1 at " << t1y << ", " << t1x << " r=" << t1r << " h=" << t1h << endl;
//                if (mode == 2) {
//                    cout << " Interfering with: ";
//                    float shiftX = t2x - t1x;
//                    float shiftY = t2y - t1y;
//                    int sector = 0;
//                    if (calcHypotenuse2(shiftX, shiftY) <= (t1r + t2r) * (t1r + t2r)) {
//                        float r = sqrt(calcHypotenuse2(shiftX, shiftY));
//                        float numAngle = shiftY / r;
//
//                        float arcCos = acos(numAngle);
//
//                        sector = (int)((arcCos * 8) / PI);
//                        assert(sector >= 0 && sector <= 7);
//                        cout << "COMPASS: " << sector << endl;
//                    }
//                }
//                cout << "2 at " << t2y << ", " << t2x << " r=" << t2r << " h=" << t2h << endl;
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
//            t1r += nEpochs * r_incr;
//            t2r += nEpochs * r_incr;

//            t1h += nEpochs * h_incr;
//            t2h += nEpochs * h_incr;
        } else if (command == "END") {
            break;
        } else {
            cout << "Unknow command" << endl;
        }
    }
}

int main() {
    treeGame();
    return 0;
}

/*
ADD 1 0.0 0.0 2 2
ADD 2 -2.0 -2.0 1 4
PRT 2
PRT 3 -5 5 -5 5
END*/
