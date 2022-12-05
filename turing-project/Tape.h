#ifndef TAPE_H
#define TAPE_H

#include <list>
#include <string>
#include <iostream>

using namespace std;

struct Ele {
    int idx;
    char ch;
    Ele(int i, char c): idx(i), ch(c) {}
};

class Tape {
private:
    int index{0};
    list<Ele> data{};
    std::list<Ele>::iterator head{};
    void trim();
public:
    Tape(int idx):index(idx) {}
    
    void load(string s, int initial_head);

    void move_left();

    void move_right();

    int current_head();

    char get();

    void print();

    void set(char ch);

    string output();
};


#endif
