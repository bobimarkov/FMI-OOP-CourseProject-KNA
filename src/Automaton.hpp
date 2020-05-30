#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

struct Transition {
    int from, to;
    char letter;

    Transition();
    Transition(int, char, int);

    bool operator== (const Transition);
};

class Automaton {
    private:
        int id;
        std::set<int> states;
        std::vector<Transition> transitions;
        std::set<int> beginningStates;
        std::set<int> endingStates;

    public:
        Automaton();
        Automaton(const Automaton&);
        Automaton(int, std::set<int>, std::vector<Transition>, std::set<int>, std::set<int>);

        Automaton& operator = (const Automaton&);

        static bool isLetter (char);

        int getID() const;
        std::vector<Transition> getTransitions() const;
        std::set<int> getStates() const;
        std::set<int> getBeginningStates() const;
        std::set<int> getEndingStates() const;

        void setID(int);
        void setTransitions(std::vector<Transition>);
        void setStates(std::set<int>);
        void setBeginningStates(std::set<int>);
        void setEndingStates(std::set<int>);

        void addTransition(Transition);
        void addState(int);
        void addBeginningState(int);
        void addEndingState(int);

        void removeTransition(Transition);
        void removeState(int);
        void removeBeginningState(int);
        void removeEndingState(int);

        void determinite();
        bool isFiniteLang() const;

        void write (std::ofstream&);
        void read (std::ifstream&);

};

#endif