#ifndef AUTOMATONLIST_HPP
#define AUTOMATONLIST_HPP

#include "Automaton.hpp"

#include <iostream>
#include <vector>

///Съхранява самият списък с отворени автомати.

class AutomatonList {
    public:
        static std::vector<Automaton> automatons;
};

#endif