#include <iostream>
#include <string>

using namespace std;

int secondGroupProject() {
    int activePlayer = 1;

    int p1y = 0;
    int p1x = 0;
    bool p1GuessedPassword = false;

    int p2y = 0;
    int p2x = 0;
    bool p2GuessedPassword = false;

    int wall1y = 0;
    int wall1x = -5;

    int wall2y = 3;
    int wall2x = -3;

    int treasury = 0;
    int treasurx = -6;

    int trapdoorx = 3;
    int trapdoory = 0;

    unsigned char password = 123;

    while (true) {
        string command;
        cin >> command;
        cout << "Processing " << command << endl;
        if (command == "HLP") {
            cout << "P b1 ... b8 -- the actual players specifes the secret password as the sequene b1 ... b8" << endl;
            // and other commands
        } else if (command == "PRT") {
            char mode;
            cin >> mode;
            if (mode == '-') {
                cout << "Active Player: " << activePlayer << " ";
                cout << " In Dungeon: ";
                if (activePlayer == 1) {
                    if (p1GuessedPassword) {
                        cout << "T ";
                    } else {
                        cout << "F ";
                    }
                }
                if (activePlayer == 2) {
                    if (p1GuessedPassword) {
                        cout << "T";
                    } else {
                        cout << "F";
                    }
                }
                cout << "Coordinates: ";
                if (activePlayer == 1) {
                    cout << p1y << ", " << p1x;
                } else if (activePlayer == 2) {
                    cout << p2y << ", " << p2x;
                }
                cout << endl;
            }
        } else if (command == "END") {
            return 0;
        } else if (command == "PSS") {
            if (activePlayer == 1) {
                if (!p1GuessedPassword) {
                    bool passwordGuessed = true;
                    for (int i = 0; i < sizeof(unsigned char) * 8; i++) {
                        char bitProvidedByUser;
                        cin >> bitProvidedByUser;
                        unsigned char flag = 1 << (sizeof(unsigned char) * 8 - 1 - i);
                        unsigned char bitValueAt = password & flag;
                        //cout << bitValueAt;
                        int bitAtPosition = bitValueAt >> (sizeof(unsigned char) * 8 - 1 - i);
                        if (bitAtPosition != (int)bitProvidedByUser - 48) {
                            passwordGuessed = false;
                        }
                    }
                    if (passwordGuessed) {
                        p1GuessedPassword = true;
                        cout << "PASSWORD GUESSED" << endl;
                    } else {
                        cout << "TRY AGAIN" << endl;
                    }
                } else {
                    cout << "PASSWORD ALREADY STATED" << endl;
                }
            }
            if (activePlayer == 2) {
                if (!p2GuessedPassword) {
                    bool passwordGuessed = true;
                    for (int i = 0; i < 8; i++) {
                        int bitValue;
                        cin >> bitValue;
                        // Use bit operations to compare the bits of the password with the provided bit.
                    }
                    if (passwordGuessed) {
                        p2GuessedPassword = true;
                        cout << "PASSWORD GUESSED" << endl;
                    } else {
                        cout << "TRY AGAIN" << endl;
                    }
                } else {
                    cout << "PASSWORD ALREADY STATED" << endl;
                }
            }
        } else if (command == "MOV") {
            if (activePlayer == 1) {
                if (p1GuessedPassword) {
                    char direction;
                    cin >> direction;
                    if (direction == 'N') {
                        p1y--;
                    }
                    if (direction == 'S') {
                        p1y++;
                    }
                    if (direction == 'E') {
                        p2x++;
                    }
                    if (direction == 'W') {
                        p2x--;
                    }
                } else {
                    cout << "GUESS PASSWORD FIRST" << endl;
                }
            }
        } else {
            cout << "UNKNOWN COMMAND: " << command << endl;
            return -1;
        }

        activePlayer++;
        if (activePlayer == 3) {
            activePlayer = 1;
        }
    }
}