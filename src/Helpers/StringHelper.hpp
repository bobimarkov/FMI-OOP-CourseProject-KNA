#ifndef STRINGHELPER_HPP
#define STRINGHELPER_HPP
#include <iostream>

class StringHelper {
    public:
        static int count (std::string str, const char c);
        static int count (std::string str, std::string c);
        static int countQ (std::string str, const char c);
        static std::string* split (std::string str, const char c);
        static std::string* split (std::string str);
        static std::string* splitQ (std::string str, const char c);
        static std::string* splitQ (std::string str);
        static std::string strip (std::string str, const char c);
        static std::string strip (std::string str);
        static std::string stripBegin (std::string str, const char c);
        static std::string stripBegin (std::string str);
        static std::string reverse (std::string str);
        static std::string toLowerCase (std::string str);
        static std::string toUpperCase (std::string str);
        static std::string clearAllConsecutiveSpaces (std::string str); 
        static std::string clearAllConsecutiveSpacesQ (std::string str); 
        static bool isAllLetters (std::string str);
        static bool isNumber(std::string str);
        static bool isLowercase (std::string str);
        static bool isUppercase (std::string str);
        static bool contains (std::string str, const char c);
        static bool contains (std::string str, std::string c);
};

#endif