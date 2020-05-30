#include "AutomatonOperations.hpp" 
#include "Automaton.hpp"
#include "AutomatonList.hpp"

#include <iostream>
#include <set>
#include <vector>

Automaton AutomatonOperations::automatonUnion(const Automaton& first, const Automaton& second) {
    Automaton newAutomaton = first;
    newAutomaton.setID(AutomatonList::automatons.size());
    
    int firstLastState = *(--newAutomaton.getStates().end());

    for(int secondState : second.getStates()) {
        newAutomaton.addState(secondState + firstLastState);
        if (second.getBeginningStates().count(secondState) != 0) newAutomaton.addBeginningState(secondState + firstLastState);
        if (second.getEndingStates().count(secondState) != 0) newAutomaton.addEndingState(secondState + firstLastState);
    }

    for(Transition secondTransition : second.getTransitions()) {
        newAutomaton.addTransition(Transition(secondTransition.from + firstLastState, secondTransition.letter, secondTransition.to + firstLastState));
    }

    int newState = *(--newAutomaton.getStates().end()) + 1;

    newAutomaton.addState(newState);

    for(int begState : newAutomaton.getBeginningStates()) {
        newAutomaton.addTransition(Transition(newState, (char)238, begState));
    }

    newAutomaton.addBeginningState(newState);

    return newAutomaton;
}

Automaton AutomatonOperations::automatonConcat(const Automaton& first, const Automaton& second) {
    Automaton newAutomaton;
    newAutomaton.setID(AutomatonList::automatons.size());
    newAutomaton.setStates(first.getStates());
    newAutomaton.setBeginningStates(first.getBeginningStates());
    newAutomaton.setTransitions(first.getTransitions());

    int firstLastState = *(--newAutomaton.getStates().end());

    for(int secondState : second.getStates()) {
        newAutomaton.addState(secondState + firstLastState);
        if (second.getEndingStates().count(secondState) != 0) newAutomaton.addEndingState(secondState + firstLastState);
    }

    for(Transition transition : second.getTransitions()) {
        newAutomaton.addTransition(Transition(transition.from + firstLastState, transition.letter, transition.to + firstLastState));
    }

    bool isSecondBeginningAlsoAnEnding = false;
    for(int firstEndingState : first.getEndingStates()) {
        for(int secondBeginningState : second.getBeginningStates()) {
            newAutomaton.addTransition(Transition(firstEndingState, (char)238, secondBeginningState + firstLastState));
            if (second.getEndingStates().count(secondBeginningState) != 0) isSecondBeginningAlsoAnEnding = true;
        }   
    }

    if (!isSecondBeginningAlsoAnEnding) {
        for(int firstEndingState : first.getEndingStates()) {
            newAutomaton.addEndingState(firstEndingState);
        }
    }

    return newAutomaton;
}

Automaton AutomatonOperations::automatonUN(const Automaton& automaton) {
    Automaton newAutomaton = automaton;
    newAutomaton.setID(AutomatonList::automatons.size());

    for (int endingState : newAutomaton.getEndingStates()) {
        if (newAutomaton.getBeginningStates().count(endingState) != 0) newAutomaton.removeEndingState(endingState);
        else {
            for(int beginningState : newAutomaton.getBeginningStates()) {
                newAutomaton.addTransition(Transition(endingState, (char)238, beginningState));
            }
        }
    }

    return newAutomaton;
}

Automaton AutomatonOperations::automatonKleeneStar(const Automaton& automaton) {
    Automaton newAutomaton = automaton;
    newAutomaton.setID(AutomatonList::automatons.size());

    bool toBeAddedNewState = true;

    for (int endingState : newAutomaton.getEndingStates()) {
        if (newAutomaton.getBeginningStates().count(endingState) != 0) toBeAddedNewState = false;
        else {
            for(int beginningState : newAutomaton.getBeginningStates()) {
                newAutomaton.addTransition(Transition(endingState, (char)238, beginningState));
            }
        }
    }

    if (toBeAddedNewState) {
        newAutomaton.addState(*(--newAutomaton.getStates().end())+1);
        newAutomaton.addBeginningState(*(--newAutomaton.getStates().end())+1);
        newAutomaton.addEndingState(*(--newAutomaton.getStates().end())+1);
    }

    return newAutomaton;
}

Automaton createAutomateFromLetter (char letter) {
    return Automaton(-1, {1, 2}, {Transition(1, letter, 2)}, {1}, {2});
}

void processOperation (std::string regex, Automaton& mainAutomaton) {
    Automaton secondAutomaton;
    
    char operation = regex[0];
    
    std::string secondArgument = regex.substr(1);
    
    if (secondArgument.length() > 1) secondAutomaton = AutomatonOperations::convertRegex(secondArgument);
    else if (secondArgument.length() == 1) secondAutomaton = createAutomateFromLetter(secondArgument[0]);

    if (operation == '+') mainAutomaton = AutomatonOperations::automatonUnion(mainAutomaton, secondAutomaton);
    else if(operation == '.') mainAutomaton = AutomatonOperations::automatonConcat(mainAutomaton, secondAutomaton);
    else if(operation == '*') mainAutomaton = AutomatonOperations::automatonKleeneStar(mainAutomaton);
}

Automaton AutomatonOperations::convertRegex (std::string regex) {
    Automaton newAutomaton;
    for (int i = 0; i < regex.length(); i++) {
        if (Automaton::isLetter(regex[i])) {
            newAutomaton = createAutomateFromLetter(regex[i]);
            regex.erase(regex.begin() + i);
            break;
        }
    }
    std::cout << regex << std::endl;
    while (regex.length() > 0) {
        int partBegin = -1;
        int bracketControl = 0;
        for (int i = 0; i < regex.length(); i++) {
            if (regex[i] == ')' && regex[i-1] == '(') {
                regex.erase(i-1,2);
                break;
            }
            if (regex[i] == '*' && partBegin == -1) {
                processOperation("" + regex[i], newAutomaton);
                regex.erase(regex.begin() + i);
                break;
            }
            if ((regex[i] == '+' || regex[i] == '.') && partBegin == -1) partBegin = i;
            if (partBegin != -1 && regex[i] == '(') bracketControl++;
            if (partBegin != -1 && regex[i] == ')') bracketControl--;
            if (bracketControl < 0) {
                std::string miniExpression = regex.substr(partBegin, i - partBegin);
                processOperation(miniExpression, newAutomaton);
                regex.erase(partBegin, i - partBegin);
                break;
            }
        }
        std::cout << "Regex size: " << regex.length() << std::endl;
        std::cout << regex << std::endl;
    }
    return newAutomaton;
}

bool recognizeRecursion (int currentState, std::set<int> endingStates, std::vector<Transition> transitions, std::string word, int currentPosWord) {
    if (currentPosWord == word.length() && endingStates.count(currentState) != 0) return true;  
    for (Transition t : transitions) {
        if (currentState == t.from && word[currentPosWord] == t.letter ) {
            if (recognizeRecursion(t.to, endingStates, transitions, word, currentPosWord+1)) return true;
        }
    }
    return false;
}

bool AutomatonOperations::automatonWordRecognition(Automaton& automaton, std::string word) {
    bool recognized = false;
    for(int beginningState : automaton.getBeginningStates()) {
        recognized = recognizeRecursion(beginningState, automaton.getEndingStates(), automaton.getTransitions(), word, 0);
        if (recognized) break;
    }
    return recognized;
}
