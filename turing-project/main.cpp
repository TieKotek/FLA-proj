#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "TM.h"

using namespace std;

bool can_open(string path) {
    ifstream f;
    f.open(path);
    if (f.is_open()) {
        f.close();
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    TM t;
    bool verbose = 0;
    if (argc == 1) {
        cerr << "Illegal usage" << endl;
        return 1;
    } else if (argc == 2) {
        string str = argv[1];
        if (str == "--help" || str == "-h") {
            cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>"
                 << endl;
            return 0;
        } else {
            cerr << "Illegal usage" << endl;
            return 1;
        }
    } else if (argc == 3 || argc == 4 || argc == 5) {
        string str1, str2;
        if (argc == 4) {
            str1 = argv[2];
            str2 = argv[3];
            string str3 = argv[1];
            if (str3 == "--verbose" || str3 == "-v") {
                verbose = 1;
                t.set_verbose(1);
            } else if (str3 == "--help" || str3 == "-h") {
                cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>"
                     << endl;
            } else {
                cerr << "illegal usage" << endl;
                return 1;
            }
        } else if (argc == 5) {
            str1 = argv[3];
            str2 = argv[4];
            string str3 = argv[1];
            string str4 = argv[2];
            if ((str3 == "--help" || str3 == "-h") &&
                    (str4 == "--verbose" || str3 == "-v") ||
                (str4 == "--help" || str4 == "-h") &&
                    (str3 == "--verbose" || str3 == "-v")) {
                t.set_verbose(1);
                cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>"
                     << endl;
            }
        } else {
            str1 = argv[1];
            str2 = argv[2];
        }
        if (str1[0] == '-') {
            cerr << "Illegal usage" << endl;
            return 1;
        } else {
            if (can_open(str1)) {
                if (t.load(str1)) {
                    if (str2[0] == '-') {
                        cerr << "Illegal usage" << endl;
                        return 1;
                    } else {
                        bool succ_input = t.set_input(str2);
                        if (!succ_input) {
                            if (!verbose) cerr << "Illegal input" << endl;
                            return 1;
                        }
                    }
                } else {
                    cerr << "Syntax error" << endl;
                    return 1;
                }
            } else {
                cerr << "Illegal usage" << endl;
                return 1;
            }
        }
    } else {
        cerr << "Illegal usage" << endl;
        return 1;
    }
    t.run();
    return 0;
}