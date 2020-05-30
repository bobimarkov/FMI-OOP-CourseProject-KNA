#include "Automaton.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

Transition::Transition() {

}

Transition::Transition(int from, char letter, int to): from(from), letter(letter), to(to) {
    
}

bool Transition::operator== (const Transition other) {
    return this -> from == other.from && this -> letter == other.letter && this -> to == other.to;
}

Automaton::Automaton() {

}

Automaton::Automaton(const Automaton& other): id(other.id), states(other.states), transitions(other.transitions), beginningStates(other.beginningStates), endingStates(other.endingStates) {

}

Automaton::Automaton(int id, std::set<int> states, std::vector<Transition> transitions, std::set<int> beginningStates, std::set<int> endingStates): id(id), states(states), transitions(transitions), beginningStates(beginningStates), endingStates(endingStates) {

}

Automaton& Automaton::operator = (const Automaton& other) {
    if (this == &other) return *this; 
    this -> id = other.id;
    this -> states = other.states;
    this -> transitions = other.transitions;
    this -> beginningStates = other.beginningStates;
    this -> endingStates = other.endingStates;
    return *this;
}

bool Automaton::isLetter (char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == 238); //238 в ASCII таблицата е епсилон
}

int Automaton::getID() const {
    return this -> getID();
}

std::vector<Transition> Automaton::getTransitions() const {
    return this -> transitions;
}

std::set<int> Automaton::getStates() const {
    return this -> states;
}

std::set<int> Automaton::getBeginningStates() const {
    return this -> beginningStates;
}

std::set<int> Automaton::getEndingStates() const {
    return this -> endingStates;
}

void Automaton::setID(int id) {
    this -> id = id;
}

void Automaton::setTransitions(std::vector<Transition> other) {
    this -> transitions = other;
}

void Automaton::setStates(std::set<int> other) {
    this -> states = other;
}

void Automaton::setBeginningStates(std::set<int> other) {
    this -> beginningStates = other;
}

void Automaton::setEndingStates(std::set<int> other) {
    this -> endingStates = other;
}

void Automaton::addTransition(Transition other) {
    transitions.push_back(other);
}

void Automaton::addState(int other) {
    states.insert(other);
}

void Automaton::addBeginningState(int other) {
    beginningStates.insert(other);
}

void Automaton::addEndingState(int other) {
    endingStates.insert(other);
}

void Automaton::removeTransition(Transition other) {
    std::vector<Transition>::iterator transitionPos = std::find(transitions.begin(), transitions.end(), other);
    transitions.erase(transitionPos);
}

void Automaton::removeState(int other) {
    states.erase(other);
}

void Automaton::removeBeginningState(int other) {
    beginningStates.erase(other);
}

void Automaton::removeEndingState(int other) {
    endingStates.erase(other);
}

void Automaton::write (std::ofstream& out) {
    out.write(reinterpret_cast<char*>(&id), sizeof(id));

    int statesSize = states.size();
    out.write(reinterpret_cast<char*>(&statesSize), sizeof(statesSize));
    for(int x : states) {
        out.write(reinterpret_cast<char*>(&x), sizeof(x));
    }

    int transitionsSize = transitions.size();
    out.write(reinterpret_cast<char*>(&transitionsSize), sizeof(transitionsSize));
    for(Transition x : transitions) {
        out.write(reinterpret_cast<char*>(&x), sizeof(x));
    }

    int beginningStatesSize = beginningStates.size();
    out.write(reinterpret_cast<char*>(&beginningStatesSize), sizeof(beginningStatesSize));
    for(int x : beginningStates) {
        out.write(reinterpret_cast<char*>(&x), sizeof(x));
    }

    int endingStatesSize = endingStates.size();
    out.write(reinterpret_cast<char*>(&endingStatesSize), sizeof(endingStatesSize));
    for(int x : endingStates) {
        out.write(reinterpret_cast<char*>(&x), sizeof(x));
    }
}

void Automaton::read (std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));

    int statesSize;
    in.read(reinterpret_cast<char*>(&statesSize), sizeof(statesSize));
    for(int i = 0; i < statesSize; i++) {
        int x;
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
        int x;
        in.read(reinterpret_cast<char*>(&x), sizeof(x));
        beginningStates.insert(x);
    }

    int endingStatesSize;
    in.read(reinterpret_cast<char*>(&endingStatesSize), sizeof(endingStatesSize));
    for(int i = 0; i < endingStatesSize; i++) {
        int x;
        in.read(reinterpret_cast<char*>(&x), sizeof(x));
        endingStates.insert(x);
    }
}