#include "Automaton.hpp"
#include "AutomatonList.hpp"

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

std::set<char> Automaton::getAlphabet() {
    std::set<char> alphabet;
    for (Transition transition : transitions) {
        if (transition.letter != (char)238) alphabet.insert(transition.letter);
    }
    return alphabet;
}

int Automaton::getID() const {
    return this -> id;
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
    id = AutomatonList::automatons.size()+1;

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

bool equalSets(std::set<int> s1, std::set<int> s2) {
    if (s1.size() == s2.size()) {
        for (int x : s1) {
            if (s2.count(x) == 0) return false;
        }
        return true; 
    }
    else return false;
}

bool containsInMainColumn(std::vector<std::vector<std::set<int>>> grid, std::set<int> state) {
    for (int i = 0; i < grid.size(); i++) {
        if (equalSets(grid[i][0], state)) return true;       
    }
    return false;
}

void Automaton::determinite() {
    std::set<char> alphabet = getAlphabet();
    std::vector<std::vector<std::set<int>>> grid;

    std::set<int> beginningState;
    for (int begState : beginningStates) beginningState.insert(begState);

    for(std::set<int>::iterator begState = beginningState.begin(); begState != beginningState.end(); begState++) {
        for(Transition transition : transitions) {
            if (transition.letter == (char)238 && transition.from == *begState && beginningState.count(transition.to) == 0) {
                beginningState.insert(transition.to);
                begState = beginningState.begin();
            }
        }
    }

    grid.push_back(std::vector<std::set<int>>(1 + alphabet.size()));
    grid[0][0] = beginningState;
    for (int i = 0; i < grid.size(); i++) {
        for(int j = 1; j < grid[i].size(); j++) {
            std::set<int> newState;
            for (int state : grid[i][0]) {
                for (Transition transition : transitions) {
                    if (transition.from == state && transition.letter == *std::next(alphabet.begin(), j-1)) newState.insert(transition.to);
                }
            }

            for(std::set<int>::iterator state = newState.begin(); state != newState.end(); state++) {
                for(Transition transition : transitions) {
                    if (transition.letter == (char)238 && transition.from == *state && newState.count(transition.to) == 0) {
                        newState.insert(transition.to);
                        state = newState.begin();
                    }
                }
            }

            grid[i][j] = newState;
            if (!containsInMainColumn(grid, newState) && newState.size() > 0) {
                grid.push_back(std::vector<std::set<int>>(1 + alphabet.size()));
                grid.back()[0] = newState;
            } 
        }
    }

    std::vector<std::vector<int>> simpleGrid(grid.size(), std::vector<int>(grid[0].size()));
    for(int i = 0; i < simpleGrid.size(); i++) simpleGrid[i][0] = i+1;

    for (int i = 0; i < grid.size(); i++) {
        for(int j = 1; j < grid[i].size(); j++) {
            for(int n = 0; n < grid.size(); n++) {
                if (equalSets(grid[n][0], grid[i][j])) simpleGrid[i][j] = n + 1;
            }
        }
    }

    Automaton newAutomaton;
    for(int i = 0; i < simpleGrid.size(); i++) newAutomaton.addState(i+1);
    newAutomaton.addBeginningState(1);
    newAutomaton.setID(id);

    for (int i = 0; i < simpleGrid.size(); i++) {
        for (int j = 1; j < simpleGrid[i].size(); j++) {
            if (simpleGrid[i][j] > 0) newAutomaton.addTransition(Transition(simpleGrid[i][0], *std::next(alphabet.begin(), j - 1), simpleGrid[i][j]));
        }
    }

    for (int i = 0; i < grid.size(); i++) {
        for(int endingState : endingStates) {
            if (grid[i][0].count(endingState) != 0) newAutomaton.addEndingState(i+1);
        }
    }

    *this = newAutomaton;
}

bool cycleRecursion (int currentState, std::set<int> endingStates, std::vector<Transition> transitions, std::set<int> passedStates ) {
    passedStates.insert(currentState);
    int fromTransitions = 0;
    for(Transition t : transitions) {
        if (currentState == t.from) fromTransitions++;
    }
    if (fromTransitions == 0) return false;  

    for (Transition t : transitions) {
        if (currentState == t.from && passedStates.count(t.to) != 0) return true; 
        if (currentState == t.from && passedStates.count(t.to) == 0) {
            if (cycleRecursion(t.to, endingStates, transitions, passedStates)) return true;
        }
    }
    return false;
}

bool Automaton::isFiniteLang() const {
    bool cycle = false;
    for(int beginningState : beginningStates) {
        cycle = cycleRecursion(beginningState, endingStates, transitions, {});
        if (cycle) break;
    }
    return !cycle;   
}