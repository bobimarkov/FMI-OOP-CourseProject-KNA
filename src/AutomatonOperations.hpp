#ifndef AUTOMATONOPERATIONS_HPP
#define AUTOMATONOPERATIONS_HPP

#include "Automaton.hpp"

#include <iostream>

///Съхранява операции с автомати.

class AutomatonOperations {
    public:

        ///Обединява два автомата.
        static Automaton automatonUnion(const Automaton&, const Automaton&);

        ///Конкатенира два автомата.
        static Automaton automatonConcat(const Automaton&, const Automaton&);

        ///Намира и връща позитивната обвивка на автомат.
        static Automaton automatonUN(const Automaton&);

        ///Намира и връща звездата на Клини за даден автомат.
        static Automaton automatonKleeneStar(const Automaton&);

        ///Преобразува регулярен израз в автомат.
        static Automaton convertRegex (std::string);

        ///Проверява дали дадена дума се разпознава от автомат.
        static bool automatonWordRecognition(Automaton&, std::string);       
};

#endif