#include "Tape.h"

using namespace std;

int get_len(unsigned int num) {
    if (num == 0) return 1;
    int res = 0;
    while(num) {
        res++;
        num /= 10;
    }
    return res;
}

void Tape::load(string s, int initial_head) {
    data.clear();
    if (s.length() == 0) {
        data.push_back(Ele(initial_head, '_'));
        head = data.begin();
    }
    else {
        for (int i = 0; i < s.length(); i++) {
            data.push_back(Ele(initial_head + i, s[i]));
        }
        head = data.begin();
    }
}

void Tape::move_left() {
    if (head == data.begin()) {
        Ele newEle((*head).idx - 1, '_');
        data.push_front(newEle);
        head = data.begin();
    }
    else {
        head--;
    }
    trim();
}

void Tape::move_right() {
    int tmp_idx = (*head).idx;
    head++;
    if (head == data.end()) {
        Ele newEle(tmp_idx + 1, '_');
        data.push_back(newEle);
        head = prev(data.end());
    }
    trim();
}

void Tape::trim() {
    while((*data.begin()).ch == '_' && head != data.begin()) {
        data.pop_front();
    }
    while((*prev(data.end())).ch == '_' && head != prev(data.end())) {
        data.pop_back();
    }
}

int Tape::current_head() {
    return (*head).idx;
}

char Tape::get() {
    return (*head).ch;
}

void Tape::set(char ch) {
    (*head).ch = ch;
    trim();
}

string Tape::output() {
    string result = "";
    if (data.size() == 1 && (*head).ch == '_') return "";
    for (auto ite = data.begin(); ite != data.end(); ite++) {
        result.push_back((*ite).ch);
    }
    return result;
}

void Tape::print() {
    trim();
    cout << "Index" << index << " : ";
    for (auto ite = data.begin(); ite != data.end(); ite++) {
        cout << abs((*ite).idx) << " ";
    }
    cout << endl;
    cout << "Tape" << index << "  : ";
    for (auto ite = data.begin(); ite != data.end(); ite++) {
        cout << (*ite).ch;
        int len = get_len(abs((*ite).idx));
        for (int i = 1; i <= len; i++) printf(" ");
    }
    cout <<endl;
    cout << "Head" << index << "  : ";
    for (auto ite = data.begin(); ite != data.end(); ite++) {
        if (ite == head) {
            cout << "^";
        }
        else cout << " ";
        int len = get_len(abs((*ite).idx));
        for (int i = 1; i <= len; i++) printf(" ");
    }
    cout <<endl;
}