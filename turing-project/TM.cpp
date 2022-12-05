#include "TM.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool Q_is_legal(char x) {
    if ('a' <= x && x <= 'z' || 'A' <= x && x <= 'Z' || '0' <= x && x <= '9' || x == '_') return true;
    return false;
}

bool S_is_legal(char x) {
    if (x == ' ' || x == ',' || x == ';' || x == '{' || x == '}' || x == '*' || x == '_') return false;
    return true;
}

bool G_is_legal(char x) {
    if (x == ' ' || x == ',' || x == ';' || x == '{' || x == '}' || x == '*') return false;
    return true;
}

int is_num(string s) {
    int ans = 0;
    for (int i = 0; i < s.length(); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            ans = ans * 10 + s[i] - '0';
        }
        else return -1;
    }
    return ans;
}

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}

bool match(string s, string pattern) {
    if (s.length() != pattern.length()) return false;
    for (int i = 0; i < s.length(); i++) {
        if (pattern[i] != s[i] && (pattern[i] != '*' || pattern[i] == '*' && s[i] == '_')) return false; 
    }
    return true;
}

bool TM::load(string file_path) {
    init();
    ifstream infile;
    infile.open(file_path);
    if (!infile.is_open()) return false;
    string line;
    int tot = 0;
    while (getline(infile, line)) {
        if (line.length() == 0 || line[0] == ';' ) continue;
        if (line[0] == '#' && line.length() >= 6) {
            if (line.substr(0, 6) == "#Q = {") {
                int idx = 6;
                tot++;
                while (1) {
                    int count = 0;
                    while(Q_is_legal(line[idx + count])) count++;
                    if (line[idx + count] == ',') {
                        _state_set.insert(line.substr(idx, count));
                        idx += count + 1;
                    }
                    else if (line[idx + count] == '}') {
                        _state_set.insert(line.substr(idx, count));
                        break;
                    }
                    else {
                        init();
                        infile.close();
                        return false;
                    }
                }
                for (auto ite = _state_set.begin(); ite != _state_set.end(); ite++) {
                    map<string, TransitionOutput> temp{};
                    _trans_fun.insert(pair<string, map<string, TransitionOutput> >(*ite, temp));
                }
            }
            if (line.substr(0, 6) == "#S = {") {
                int idx = 6;
                tot++;
                while(1) {
                    string pattern = line.substr(idx, 2);
                    if (pattern.length() < 2) {
                        init();
                        infile.close();
                        return false;
                    }
                    if (pattern[1] == ',') {
                        if (S_is_legal(pattern[0])) {
                            _input_set.insert(pattern[0]);
                        }
                        else {
                            init();
                            infile.close();
                            return false;
                        }
                        idx += 2;
                    }
                    else if (pattern[1] == '}') {
                        if (S_is_legal(pattern[0])) {
                            _input_set.insert(pattern[0]);
                        }
                        else {
                            init();
                            infile.close();
                            return false;
                        }
                        break;
                    }
                    else {
                        init();
                        infile.close();
                        return false;
                    }
                }
            }
            if (line.substr(0, 6) == "#G = {") {
                int idx = 6;
                tot++;
                while(1) {
                    string pattern = line.substr(idx, 2);
                    if (pattern[1] == ',') {
                        if (G_is_legal(pattern[0])) {
                            _tape_set.insert(pattern[0]);
                        }
                        else {
                            init();
                            infile.close();
                            return false;
                        }
                        idx += 2;
                    }
                    else if (pattern[1] == '}') {
                        if (G_is_legal(pattern[0])) {
                            _tape_set.insert(pattern[0]);
                        }
                        else {
                            init();
                            infile.close();
                            return false;
                        }
                        break;
                    }
                    else {
                        init();
                        infile.close();
                        return false;
                    }
                }
            }
            if (line.substr(0, 6) == "#q0 = ") {
                tot++;
                if (_state_set.empty()) {
                    init();
                    infile.close();
                    return false;
                }
                if (_state_set.find(line.substr(6)) != _state_set.end()) {
                    _state = line.substr(6);
                }
                else {
                    init();
                    infile.close();
                    return false;
                }
            }
            if (line.substr(0, 5) == "#B = ") { tot++; continue;}
            if (line.substr(0, 6) == "#F = {") {
                int idx = 6;
                tot++;
                while (1) {
                    int count = 0;
                    while(Q_is_legal(line[idx + count])) count++;
                    if (line[idx + count] == ',') {
                        if (_state_set.find(line.substr(idx, count)) != _state_set.end()) {
                            _accept_states.insert(line.substr(idx, count));
                            idx += count + 1;
                        }
                        else {
                            init();
                            infile.close();
                            return false;
                        }
                    }
                    else if (line[idx + count] == '}') {
                        if (_state_set.find(line.substr(idx, count)) != _state_set.end()) {
                            _accept_states.insert(line.substr(idx, count));
                            idx += count + 1;
                        }
                        else {
                            init();
                            infile.close();
                            return false;
                        }
                        break;
                    }
                    else {
                        init();
                        infile.close();
                        return false;
                    }
                }
            }
            if (line.substr(0, 5) == "#N = ") {
                tot++;
                _tape_num = is_num(line.substr(5));
                if (_tape_num == -1) {
                    init();
                    return false;
                }
                for (int i = 0; i < _tape_num; i++) {
                    Tape newTape(i);
                    _tapes.push_back(newTape);
                }
            }
        }
        else if (tot >= 7) {
            vector<string> vec;
            SplitString(line, vec, " ");
            if (vec.size() < 5 || vec.size() > 5 && vec[5][0] != ';') {
                init();
                infile.close();
                return false;
            }
            if (_state_set.find(vec[0]) == _state_set.end() || _state_set.find(vec[4]) == _state_set.end()) {
                init();
                infile.close();
                return false;
            }
            if (!check(vec[1], vec[2], vec[3])) {
                init();
                infile.close();
                return false;
            }
            TransitionOutput temp(vec[3], vec[4], vec[2]); 
            _trans_fun[vec[0]][vec[1]] = temp;
        }
        else {
            init();
            infile.close();
            return false;
        }
    }

    return true;
}

bool TM::set_input(string input) {
    if (_verbose) cout << "Input: " << input << endl;
    for (int i = 0; i < input.length(); i++) {
        if (_input_set.find(input[i]) == _input_set.end()) {
            if (_verbose) {
                cout << "==================== ERR ====================" << endl;
                cout << "error: '" << input[i] << "' was not declared in the set of input symbols" << endl;
                cout << "Input: " << input << endl;
                for (int j = 1; j <= 7 + i; j++) printf(" ");
                printf("^\n");
                cout << "==================== END ====================" << endl;
            }
            return false;
        }
    }
    _tapes[0].load(input, 0);
    for (int i = 1; i < _tape_num; i++) {
        _tapes[i].load("", 0);
    }
    return true;
}

void TM::step() {
    string now_tapes = "";
    for (int i = 0; i < _tapes.size(); i++) {
        now_tapes += _tapes[i].get();
    }
    TransitionOutput output;
    if (_trans_fun[_state].find(now_tapes) != _trans_fun[_state].end()) {
        output = _trans_fun[_state][now_tapes];
    }
    else {
        bool matched = 0;
        for (auto ite = _trans_fun[_state].begin(); ite != _trans_fun[_state].end(); ite++) {
            string pattern = ite->first;
            if (match(now_tapes, pattern)) {
                output = ite->second;
                matched = 1;
                break;
            }
        }
        if (!matched) {
            _halted = 1;
            return;
        }
    }
    ++_step_counter;
    _state = output.state;
    for (int i = 0; i < _tapes.size(); i++) {
        if (output.tape_characters[i] != '*') _tapes[i].set(output.tape_characters[i]);
        if (output.directions[i] == 'l') {
            _tapes[i].move_left();
        }
        else if (output.directions[i] == 'r') {
            _tapes[i].move_right();
        }
    }
}

void TM::run() {
    _step_counter = 0;
    if (_verbose) {
        cout << "==================== RUN ====================" << endl;
    }
    while (!_halted) {
        if (_verbose) {
            cout << "Step   : "<< _step_counter << endl;
            cout << "State  : " << _state << endl;
            for (int i = 0; i < _tapes.size(); i++) {
                _tapes[i].print();
            }
            cout << "---------------------------------------------" << endl;
        }
        if (accepted()) break;
        step();
    }
    string result = _tapes[0].output();
    if (_verbose) {
        cout << "Result: " << result << endl;
        cout << "==================== END ====================" << endl;
    }
    else {
        cout << result << endl;
    }
}