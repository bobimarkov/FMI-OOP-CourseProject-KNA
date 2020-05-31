#ifndef COMMANDLINE_HPP
#define COMMANDLINE_HPP

#include "StringHelper.hpp"
#include "Automaton.hpp"
#include "AutomatonList.hpp"
#include "AutomatonOperations.hpp"
#include "RegexUtils.hpp"

#include <iostream>
#include <string>

/** Съдържа работата на командният ред.
 */


class CommandLine {
    private:
        /// Показва дали е отворен файл.
        static bool openedFile;

        /// Съхранява пътя към отвореният файл.
        static std::string openedFilePath;

        ///Съхранява името на отвореният файл.
        static std::string fileName;

        ///Взима името от openedFilePath и го слага във fileName.
        static void setFileName();  

        ///Отваря файл, с който програмата да работи.
        static void open(std::string);

        ///Затваря текущо отвореният файл.
        static void close();

        ///Запазва записаните автомати в даден файл.
        static void saveas(std::string);

        ///Запазва записаните автомати в отворения файл.
        static void save();

        ///Извежда всички команди в командният ред.
        static void help();

        ///Излиза от програмата.
        static void exit();

        ///Извежда ID-тата на всички записани автомати.
        static void list ();

        ///Извежда преходите на автомат.
        static void print (int);

        ///Запазва даден автомат в зададен файл.
        static void save (int, std::string);

        ///Проверява дали езикът на автоматът е празен.
        static void empty (int);

        ///Проверява дали автоматът е детерминиран.
        static void deterministic (int);

        ///Проверява дали дадена дума се разпознава от автомата.
        static void recognize (int, std::string); 

        ///Обединява два автомата.
        static void _union (int, int);

        ///Конкатенира два автомата.
        static void concat (int, int);

        ///Взима позитивната обвивка на автомат.
        static void un (int);

        ///Преобразува регулярен израз в автомат.
        static void reg (std::string);

        ///Детерминира автомат.
        static void determine (int);

        ///Проверява дали езика на автомата е краен.
        static void isFiniteLang (int);
    public:

        ///Пуска командният ред.
        static void run();
};
#endif