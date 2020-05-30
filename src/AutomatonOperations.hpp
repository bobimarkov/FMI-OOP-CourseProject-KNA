#ifndef AUTOMATONOPERATIONS_HPP
#define AUTOMATONOPERATIONS_HPP

#include "Automaton.hpp"

#include <iostream>

class AutomatonOperations {
    public:
        static Automaton automatonUnion(const Automaton&, const Automaton&);
        static Automaton automatonConcat(const Automaton&, const Automaton&);
        static Automaton automatonUN(const Automaton&);
        static Automaton automatonKleeneStar(const Automaton&);
        static Automaton convertRegex (std::string);
        static bool automatonWordRecognition(Automaton&, std::string);       
};

#endif