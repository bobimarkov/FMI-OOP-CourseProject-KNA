#ifndef REGEXUTILS_HPP
#define REGEXUTILS_HPP

#include <iostream>
#include <string>

class RegexUtils {
    public:
        static bool isValidRegex(std::string);
        static std::string addPointsWhereAreMissing(std::string);
};

#endif