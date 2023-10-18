#include <iostream>
#include <string>
#include <math.h>

using namespace std;

void treeGame() {
    float t1y;
    float t1x;
    float t1r;
    float t1h;
    bool t1active = false;

    float t2y;
    float t2x;
    float t2r;
    float t2h;
    bool t2active = false;

    float r_incr;
    float h_incr;

    while (true) {
        string command;
        cin >> command;
        if (command == "ADD") {
            int id;
            cin >> id;
            if (id == 1) {
                if (t1active) {
                    cout << "Tree already active" << endl;
                    continue;
                }
                cin >> t1y;
                cin >> t1x;
                cin >> t1r;
                cin >> t1h;
                t1active = true;
            }
            if (id == 2) {
                if (t2active) {
                    cout << "Tree already active" << endl;
                    continue;
                }
                cin >> t2y;
                cin >> t2x;
                cin >> t2r;
                cin >> t2h;
                t2active = true;
            }
        } else if (command == "MDL") {
            int mode;
            cin >> mode;
            if (mode == 0) {
                cin >> r_incr >> h_incr;
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
            } else {
                cout << "Trees:" << endl;
                cout << "1 at " << t1y << ", " << t1x << " r=" << t1r << " h=" << t1h << endl;
                if (mode == 2) {
                    cout << " Interfering with: ";
                    if ((t1y - t2y) * (t1y - t2y) + (t1x - t2x) * (t1x - t2x) <= (t1r + t2r) * (t1r + t2r)) {
                        cout << "2" << endl;;
                        float shiftx = t2x - t1x;
                        float shifty = t2y - t1y;
                        float r = sqrt(shiftx * shiftx + shifty * shifty);
                        float shiftx2 = shiftx / r;
                        float shifty2 = shifty / r;

                        float arccos = acos(shifty2);

                        float prevAngle = -22.5 / 180.0 * 3.1415;

                        int sector = -1;
                        for (int i = 0; i < 8; i++) {
                            float angle = prevAngle + 45.0 / 180.0 * 3.1415;
                            if (arccos >= prevAngle && arccos <= angle) {
                                sector = i;
                            }
                            prevAngle = angle;
                        }
                        if (sector == -1) {
                            cout << "???";
                            return;
                        }

//                        if (sector == -1) {
//                            cout << "ERROR" << endl;
//                            return;
//                        }
                    }
                    cout << endl;
                }
                cout << "2 at " << t2y << ", " << t2x << " r=" << t2r << " h=" << t2h << endl;
                if (mode == 2) {
                    cout << " Interfering with: ";
                    if ((t1y - t2y) * (t1y - t2y) + (t1x - t2x) * (t1x - t2x) <= (t1r + t2r) * (t1r + t2r)) {
                        cout << "1";
                    }
                    cout << endl;
                }
            }
        } else if (command == "REM") {
            int id;
            if (id == 1) {
                t1active = false;
            } else if (id == 2) {
                t2active = false;
            }
        } else if (command == "ADV") {
            int nEpochs;
            cin >> nEpochs;
            t1r += nEpochs * r_incr;
            t2r += nEpochs * r_incr;

            t1h += nEpochs * h_incr;
            t2h += nEpochs * h_incr;
        } else if (command == "END") {
            break;
        } else {
            cout << "Unknow command" << endl;
        }
    }
}

/*
ADD 1 0.0 0.0 2 2
ADD 2 -2.0 -2.0 1 4
PRT 2
PRT 3 -5 5 -5 5
END*/
