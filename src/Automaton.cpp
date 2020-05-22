#include "Automaton.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

Automaton::Automaton() {

}

Automaton::Automaton(const Automaton& other): id(other.id), states(other.states), transitions(other.transitions), beginningStates(other.beginningStates), endingStates(other.endingStates) {

}

Automaton::Automaton(int id, std::unordered_set<char> states, std::vector<Transition> transitions, std::unordered_set<char> beginningStates, std::unordered_set<char> endingStates): id(id), states(states), transitions(transitions), beginningStates(beginningStates), endingStates(endingStates) {

}

Automaton& Automaton::operator = (const Automaton& other) {
    this -> id = other.id;
    this -> states = other.states;
    this -> transitions = other.transitions;
    this -> beginningStates = other.beginningStates;
    this -> endingStates = other.endingStates;
}

void Automaton::write (std::ofstream& out) {
    out.write(reinterpret_cast<char*>(&id), sizeof(id));

    int statesSize = states.size();
    out.write(reinterpret_cast<char*>(&statesSize), sizeof(statesSize));
    for(char x : states) {
        out.write(reinterpret_cast<char*>(&x), sizeof(x));
    }

    int transitionsSize = transitions.size();
    out.write(reinterpret_cast<char*>(&transitionsSize), sizeof(transitionsSize));
    for(Transition x : transitions) {
        out.write(reinterpret_cast<char*>(&x), sizeof(x));
    }

    int beginningStatesSize = beginningStates.size();
    out.write(reinterpret_cast<char*>(&beginningStatesSize), sizeof(beginningStatesSize));
    for(char x : beginningStates) {
        out.write(reinterpret_cast<char*>(&x), sizeof(x));
    }

    int endingStatesSize = endingStates.size();
    out.write(reinterpret_cast<char*>(&endingStatesSize), sizeof(endingStatesSize));
    for(char x : endingStates) {
        out.write(reinterpret_cast<char*>(&x), sizeof(x));
    }
}

void Automaton::read (std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));

    int statesSize;
    in.read(reinterpret_cast<char*>(&statesSize), sizeof(statesSize));
    for(int i = 0; i < statesSize; i++) {
        char x;
        in.read(reinterpret_cast<char*>(&x), sizeof(x));
        states.insert(x);
    }

    int transitionsSize;
    in.read(reinterpret_cast<char*>(&transitionsSize), sizeof(transitionsSize));
    for(int i = 0; i < transitionsSize; i++) {
        Transition x;
        in.read(reinterpret_cast<char*>(&x), sizeof(x));
        transitions.push_back(x);
    }

    int beginningStatesSize;
    in.read(reinterpret_cast<char*>(&beginningStatesSize), sizeof(beginningStatesSize));
    for(int i = 0; i < beginningStatesSize; i++) {
        char x;
        in.read(reinterpret_cast<char*>(&x), sizeof(x));
        beginningStates.insert(x);
    }

    int endingStatesSize;
    in.read(reinterpret_cast<char*>(&endingStatesSize), sizeof(endingStatesSize));
    for(int i = 0; i < endingStatesSize; i++) {
        char x;
        in.read(reinterpret_cast<char*>(&x), sizeof(x));
        endingStates.insert(x);
    }
}