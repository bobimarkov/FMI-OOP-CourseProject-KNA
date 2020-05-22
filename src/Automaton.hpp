#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

struct Transition {
    char from, letter, to;
};

class Automaton {
    private:
        int id;
        std::unordered_set<char> states;
        std::vector<Transition> transitions;
        std::unordered_set<char> beginningStates;
        std::unordered_set<char> endingStates;

    public:
        Automaton();
        Automaton(const Automaton&);
        Automaton(int, std::unordered_set<char>, std::vector<Transition>, std::unordered_set<char>, std::unordered_set<char>);

        Automaton& operator = (const Automaton&);

        void determinite();
        bool isStateLang();

        void write (std::ofstream&);
        void read (std::ifstream&);

};

#endif