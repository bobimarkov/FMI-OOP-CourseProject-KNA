#include <iostream>
#include "StringHelper.hpp"

//Брои броят срещания на символа c в стринга
int StringHelper::count (std::string str, const char c) {
    int counter = 0;
    for(int i = 0; i < str.length(); i++) {
        if (str[i] == c) counter++;
    }
    return counter;
}

//Брои колко са срещанията на символа с в стринга, в част, в която не е заградена от кавички
int StringHelper::countQ (std::string str, const char c) {
    int counter = 0;
    bool openQuotes = false;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] == '"') openQuotes = !openQuotes;
        if (str[i] == c && !openQuotes) {
            counter++;
        }
    }
    return counter;
}

//Брои броят срещания на даден низ в друг низ
int StringHelper::count (std::string str, std::string c) {
    int counter = 0, it = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == c[it]) {
            it++;
            for(int j = i + 1; j < str.length(); j++) {
                if(str[j] == c[it]) it++;
                else {
                    it = 0;
                    break;
                }
                if(it == c.length()) {
                    counter++;
                    it = 0;
                    break;
                }
            }
        }
    }
    return counter;
}


//Разделя даден низ на масив от поднизове спрямо даден символ (примерно "Hello World!" ще се раздели на {"Hello", "World!"})
std::string* StringHelper::split (std::string str, const char c) {
    int arrSize = count(str,c) + 1;
    std::string* array = new std::string[arrSize];
    if(arrSize == 1) {
        array[0] = str;
        return array;    
    };
    std::string tempString;
    int h = 0;
    for (int i = 0; i < str.length(); i++) {
        if(str[i] == c) {
            array[h] = tempString;
            tempString.erase();
            h++;
        }
        else {
            tempString += str[i];
        }
    }   
    array[h] = tempString;
    return array;
}

//Ако не е зададен символ по който да заделя, то заделя спрямо интервалите в низа
std::string* StringHelper::split (std::string str) {
    std::string* newString = split(str, ' ');
    return newString;
}

//Разделя даден низ на масив от поднизове спрямо даден символ като символите в кавички се игнорират (примерно <This is "Hello World!"> ще се раздели на {This,is,"Hello World!"})
std::string* StringHelper::splitQ (std::string str, const char c) {
    int arrSize = countQ(str,c) + 1;
    std::string* array = new std::string[arrSize];
    if(arrSize == 1) {
        array[0] = str;
        return array;    
    };
    std::string tempString;
    bool openedQuotes = false;
    int h = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '"') openedQuotes = !openedQuotes;
        if(str[i] == c && !openedQuotes) {
            array[h] = tempString;
            tempString.erase();
            h++;
        }
        else {
            tempString += str[i];
        }
    }   
    array[h] = tempString;
    return array;
}

//Ако не е зададен символ по който да заделя, то заделя спрямо интервалите в низа
std::string* StringHelper::splitQ (std::string str) {
    std::string* newString = splitQ(str, ' ');
    return newString;
}

//Премахва срещанията на символа c от най-вкрая на низа, ако има такива ("Dinosauroooooooooo" при указан символ 'o' ще стане "Dinosaur")
std::string StringHelper::strip (std::string str, const char c) {
    if(str.empty() || *(str.end()-1) != c) return str;
    int stopIndex = str.length()-1;
    for(int i = str.length()-2;i>=0;i--) { 
        if(str[i] == c) {
            stopIndex--;
        }
        else break;
    }
    std::string newString = str.substr(0,stopIndex);
    return newString;
}

//Ако не е зададен символ по който да премахва срещанията на символа, то премахва интервалите в низа 
std::string StringHelper::strip (std::string str) {
    std::string newString = strip(str, ' ');
    return newString;
}

//Прави същото като strip, но само де премахването се извършва в началото на низа
std::string StringHelper::stripBegin (std::string str, const char c) {
    if(str.empty() || *str.begin() != c) return str;
    int beginIndex = 0;
    for(int i = 1; i < str.length(); i++) { 
        if(str[i] == c) {
            beginIndex++;
        }
        else break;
    }
    std::string newString = str.substr(beginIndex + 1,str.length()-beginIndex);
    return newString;
}

//Ако не е зададен символ, то премахва интервалите
std::string StringHelper::stripBegin (std::string str) {
    std::string newString = stripBegin(str, ' ');
    return newString;
}

//Обръща низа
std::string StringHelper::reverse (std::string str) {
    std::string newString;
    for(int i=str.length()-1; i>=0; --i) {
        newString += str[i];
    }
    return newString;
}

//Прави всички букви малки
std::string StringHelper::toLowerCase (std::string str) {
    std::string newString = str;
    for(int i=0;i<newString.length();i++) {
        if(newString[i]>='A' && newString[i]<='Z') newString[i]+=('a'-'A');
    }
    return newString;
}

//Прави всички букви големи
std::string StringHelper::toUpperCase (std::string str) {
    std::string newString = str;
    for(int i=0;i<newString.length();i++) {
        if(newString[i]>='a' && newString[i]<='z') newString[i]-=('a'-'A');
    }
    return newString;
}

//Ако има множество от последователни интервали, то свежда интервалите до 1 ("Hello           World!" ще стане "Hello World!")
std::string StringHelper::clearAllConsecutiveSpaces (std::string str) {
    std::string newString;
    bool repeatingSpaces = false;
    for(int i = 0; i < str.length(); i++) {
        if (!repeatingSpaces) {
            if (i > 0) {
                if (str[i-1] == ' ' && str[i] == ' ') repeatingSpaces = true;
            }
            if(!repeatingSpaces) newString+= str[i];
        }
        else if (str[i] != ' ') {
            repeatingSpaces = false;
            newString += str[i];
        }
    }  
    return newString;
}

//Ако има множество от последователни интервали, то свежда интервалите до 1 като игнорира текст в кавички (<echo         "Hello     World!"> ще стане <echo "Hello     World!">)
std::string StringHelper::clearAllConsecutiveSpacesQ (std::string str) {
    std::string newString;
    bool repeatingSpaces = false, openQuotes = false;
    for(int i = 0; i < str.length(); i++) {
        if(!openQuotes) {
            if(str[i] == '"') openQuotes = true;
            if (!repeatingSpaces) {
                if (i > 0) {
                    if (str[i-1] == ' ' && str[i] == ' ') repeatingSpaces = true;
                }
                if(!repeatingSpaces) newString+= str[i];
            }
            else if (str[i] != ' ') {
                repeatingSpaces = false;
                newString += str[i];
            }
        }
        else {
            if(str[i] == '"') openQuotes = false;
            newString += str[i];
        }
    }  
    return newString;
}

//Проверява дали всичките символи в низа са букви
bool StringHelper::isAllLetters (std::string str) {
    for(int i = 0; i < str.length(); i++) {
        if(!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))) return false;
    }
    return true;
}

//Проверява дали всичките символи в низа са цифри (допуска се рационално число, затова десетична запетая)
bool StringHelper::isNumber(std::string str) {
    for(int i = 0; i < str.length(); i++) {
        if(str[i] < '0' || str[i] > '9' || count(str,'.') > 1) return false;
    }
    return true;
}

//Проверява дали всичките букви са малки
bool StringHelper::isLowercase (std::string str) {
    return str.length() != 0 && toLowerCase(str) == str;
}

//Проверява дали всичките букви са големи
bool StringHelper::isUppercase (std::string str) {
    return str.length() != 0 && toUpperCase(str) == str;
}

//Проверява дали даден символ се съдържа в низа
bool StringHelper::contains (std::string str, const char c) {
    return count(str,c) > 0;
}

//Проверява дали даден низ се съдържа в низа
bool StringHelper::contains (std::string str, std::string c) {
    int it = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == c[it]) {
            it++;
            for(int j = i + 1; j < str.length(); j++) {
                if(str[j] == c[it]) it++;
                else {
                    it = 0;
                    break;
                }
                if(it == c.length()) return true;
            }
        }
    }
    return false;
}
