# ifndef TM_H
# define TM_H

#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Tape.h"

using namespace std;

struct TransitionOutput {
    string directions;
    string state;
    string tape_characters;
    TransitionOutput(string dir, string sta, string t): directions(dir), state(sta), tape_characters(t) {}  
    TransitionOutput() {
        TransitionOutput("", "", "");
    }
};
 
class TM {
private:
    //print setting
    bool _verbose{0};
    //backup datas
    int _step_counter{0};
    bool _halted{0};
    unordered_set<string> _state_set{}, _accept_states;
    unordered_set<char> _input_set{}, _tape_set{};
    int _tape_num{0};
    unordered_map<string, unordered_map<string, TransitionOutput> > _trans_fun{};

    // turing structures
    string _state{""};
    vector<Tape> _tapes{};

    void step();

    bool check(string tape_input1, string tape_input2, string dir) {
        if (tape_input1.length() != _tape_num || tape_input2.length() != _tape_num || dir.length() != _tape_num) return false;
        for (int i = 0; i < tape_input1.length(); i++) {
            if (tape_input1[i] != '*' && _tape_set.find(tape_input1[i]) == _tape_set.end()) return false;
        }
        for (int i = 0; i < tape_input2.length(); i++) {
            if ((tape_input2[i] != '*' || tape_input2[i] == '*' && tape_input1[i] != '*' )&& _tape_set.find(tape_input2[i]) == _tape_set.end()) return false;
        }
        for (int i = 0; i < dir.length(); i++) {
            if (dir[i] != '*' && dir[i] != 'l'&& dir[i] != 'r') return false;
        }
        return true;
    }

public:
    TM() {}
    
    bool accepted() {
        if (_accept_states.find(_state) != _accept_states.end()) return true;
        else return false;
    }
   
    void init() {
        _state_set.clear();
        _accept_states.clear();
        _input_set.clear();
        _tape_set.clear();
        _tape_num = 0;
        _trans_fun.clear();
        _state = "";
        _tapes.clear();
        _halted = 0;
        _step_counter = 0;
    }

    bool halted() {
        return _halted;
    }

    void set_verbose(bool v) {
        _verbose = v;
    }

    bool load(string file_path);

    bool set_input(string input);

    void run();
};

#endif