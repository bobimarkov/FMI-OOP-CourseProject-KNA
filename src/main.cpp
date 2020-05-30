#include "Helpers/StringHelper.hpp"
#include "Automaton.hpp"
#include "AutomatonList.hpp"
#include "AutomatonOperations.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define SH StringHelper

bool openedFile = false;
std::string openedFilePath;
std::string fileName;

void setFileName () {
    int countSlash = SH::count(openedFilePath,'/');
    int countBackslash = SH::count(openedFilePath, (char)92);

    if(countSlash == 0 && countBackslash == 0) fileName = openedFilePath;
    else if (countSlash > 0) {
        std::string* sepPath = SH::split(openedFilePath,'/');
        fileName = sepPath[countSlash];
    }
    else if (countBackslash > 0) {
        std::string* sepPath = SH::split(openedFilePath,(char)92);
        fileName = sepPath[countBackslash];
    }
}

void open(std::string filePath) {
    if(!openedFile) {
        std::ifstream in (filePath, std::ios::binary | std::ios::in);

        if(!in.is_open()) {
            std::ofstream out (filePath, std::ios::binary | std::ios::out);
            out.close();    
            in.open(filePath, std::ios::binary | std::ios::in);
        }

        if(!in.is_open()) {
            std::cout << "Error: Invalid file path!\n";
            return;
        }

        in.seekg(0,std::ios::end);
        std::streampos size = in.tellg();
        in.seekg(0,std::ios::beg);

        
        openedFile = true;
        openedFilePath = filePath;
        setFileName();
        
        while(in.tellg() != size && !in.eof()) {
            Automaton a;
            a.read(in);
            AutomatonList::automatons.push_back(a);
        }

        std::cout << "Successfully opened " << fileName << "!\n";
        in.close();
    }
    else std::cerr << "There is already an opened file! You can close the file with 'close'\n"; 
}

void close() {
    if(openedFile) {
        openedFile = false;
        AutomatonList::automatons.clear();
        std::cout << "Successfully closed " << fileName << "!\n";
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void saveas(std::string filePath) {
    if (openedFile) {
        std::ofstream out(filePath, std::ios::binary | std::ios::out);

        if (!out.is_open()) {
            std::cerr << "Error: Invalid file path!\n";
            return;
        }


        openedFilePath = filePath;
        setFileName();

        for(Automaton s: AutomatonList::automatons) {
            s.write(out);
        }

        std::cout << "Successfully saved " << fileName << "!\n"; 

        out.close();
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void save() {
    if(openedFile) saveas(openedFilePath);
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void help(){
    std::cout << "Available commands:\n"
              << "help - shows all available commands\n"
              << "open <file path> - opens <file path>\n"
              << "exit - exits the program\n"
              << "\nThe following commands work only when a file is opened:\n"
              << "close - closes the current opened file\n"
              << "saveas <file path> - saves the current opened file in <file path>\n"
              << "save - saves the current opened file\n";            
}

void exit(){
    std::cout << "Exiting the program...\n";
    std::exit(0);
}


void list () {
    if (openedFile) {
        std::cout << "IDs:\n";
        for(Automaton a : AutomatonList::automatons) {
            std::cout << a.getID() << std::endl;
        }
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void print (int id) {
    if (openedFile) {
        for (Transition t : AutomatonList::automatons[id-1].getTransitions()) {
            std::cout << "<" << t.from << "," << t.letter << "," << t.to << ">\n"; 
        }
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void save (int id, std::string path) {
    if (openedFile) {
        std::ofstream out(path, std::ios::binary | std::ios::out);

        if (!out.is_open()) {
            std::cerr << "Error: Invalid file path!\n";
            return;
        }

        AutomatonList::automatons[id-1].write(out);

        std::cout << "Successfully saved automaton " << id << "in file " << fileName << "!\n"; 

        out.close();
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void empty (int id) {
    if (openedFile) {
        bool emptyAlphabet = AutomatonList::automatons[id-1].getBeginningStates().size() == 1 && AutomatonList::automatons[id-1].getStates().size() == 1 && AutomatonList::automatons[id-1].getEndingStates().size() == 0;
        std::cout << (emptyAlphabet ? "Empty!" : "Not empty!") << std::endl;
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void deterministic (int id) {
    if (openedFile) {
        bool hasEpsilonTransitions = false, hasMultipleTransitionsOneLetter = false;

        for (Transition t : AutomatonList::automatons[id-1].getTransitions()) {
            if (t.letter == 238) hasEpsilonTransitions = true;
        }

        for (char state : AutomatonList::automatons[id-1].getStates()) {
            std::vector<std::pair<char, int>> transitionsCount;
            for (Transition t : AutomatonList::automatons[id-1].getTransitions()) {
                if (t.from == state) {
                    int letterIndex = -1;
                    for(int i = 0; i < transitionsCount.size(); i++) {
                        if (t.letter == transitionsCount[i].first) letterIndex = i;
                    }
                    if (letterIndex > -1) transitionsCount[letterIndex].second++;
                    else transitionsCount.push_back(std::make_pair(t.letter, 1)); 
                }
            }

            for (std::pair<char,int> p : transitionsCount) {
                if (p.second > 1) hasMultipleTransitionsOneLetter = true;
            }
        }

        bool deterministic = AutomatonList::automatons[id-1].getBeginningStates().size() == 1 && !hasEpsilonTransitions && !hasMultipleTransitionsOneLetter;
        
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void recognize  (int id, std::string word) {
    if (openedFile) {
        if(id >= 1 && id <= AutomatonList::automatons.size()) std::cout << word << (AutomatonOperations::automatonWordRecognition(AutomatonList::automatons[id-1], word) ? " was recognized" : " wasn't recognized") << std::endl;
        else std::cerr << "Invalid id!\n";
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}
 
void _union (int id1, int id2) {
    if (openedFile) {
        if((id1 >= 1 && id1 <= AutomatonList::automatons.size()) && (id2 >= 1 && id2 <= AutomatonList::automatons.size())) {
            AutomatonList::automatons.push_back(AutomatonOperations::automatonUnion(AutomatonList::automatons[id1-1], AutomatonList::automatons[id2-1]));
            std::cout << "New automaton's id: " << AutomatonList::automatons.back().getID() << std::endl;
        }
        else std::cerr << "Invalid id!\n";
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void concat (int id1, int id2) {
    if (openedFile) {
        if((id1 >= 1 && id1 <= AutomatonList::automatons.size()) && (id2 >= 1 && id2 <= AutomatonList::automatons.size())) {
            AutomatonList::automatons.push_back(AutomatonOperations::automatonConcat(AutomatonList::automatons[id1-1], AutomatonList::automatons[id2-1]));
            std::cout << "New automaton's id: " << AutomatonList::automatons.back().getID() << std::endl;
        }
        else std::cerr << "Invalid id!\n";
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
} 

void un (int id) {
    if (openedFile) {
        if(id >= 1 && id <= AutomatonList::automatons.size()) {
            AutomatonList::automatons.push_back(AutomatonOperations::automatonUN(AutomatonList::automatons[id-1]));
            std::cout << "New automaton's id: " << AutomatonList::automatons.back().getID() << std::endl;
        }
        else std::cerr << "Invalid id!\n";
    }
    else std::cerr << "There is not opened file! You can open file with 'open <file path>'\n";
}

void reg (std::string regex) {
    //regex check here (brackets + alphabet)
    AutomatonOperations::convertRegex(regex);
}

void determine (int id) {

}

void isFiniteLang (int id) {

}

int main () {
    reg("((((((a+b)*)+(c.b))*).a)*)");
    return 0;
    std::cout << "Welcome to KNA!\n";
    while(true) {
        std::string command;
        std::cout << "\n> "; 
        getline(std::cin, command);
        command = SH::clearAllConsecutiveSpacesQ(SH::stripBegin(SH::strip(command)));
        std::string* separatedCommand = SH::splitQ(command);
        int commandArguments = SH::countQ(command, ' ') + 1;

        if (SH::toLowerCase(separatedCommand[0]) == "exit") {
           if (commandArguments > 1) std::cerr << "Too much arguments for this command!\n";
            else if (commandArguments < 1) std::cerr << "Too few arguments for this command!\n";
            else {
                delete[] separatedCommand;
                exit();
            }
        }
        else if (SH::toLowerCase(separatedCommand[0]) == "open") {
            if (commandArguments > 2) std::cerr << "Too much arguments for this command!\n";
            else if (commandArguments < 2) std::cerr << "Too few arguments for this command!\n";
            else {
                separatedCommand[1] = SH::strip(SH::stripBegin(separatedCommand[1],'"'),'"');
                open(separatedCommand[1]);
            }
        }
        else if (SH::toLowerCase(separatedCommand[0]) == "close") {
            if (commandArguments > 1) std::cerr << "Too much arguments for this command!\n";
            else if (commandArguments < 1) std::cerr << "Too few arguments for this command!\n";
            else close();
        }
        else if (SH::toLowerCase(separatedCommand[0]) == "help") {
            if (commandArguments > 1) std::cerr << "Too much arguments for this command!\n";
            else if (commandArguments < 1) std::cerr << "Too few arguments for this command!\n";
            else help();
        }
        else if (SH::toLowerCase(separatedCommand[0]) == "save") {
            if (commandArguments > 1) std::cerr << "Too much arguments for this command!\n";
            else if (commandArguments < 1) std::cerr << "Too few arguments for this command!\n";
            else save();
        }
        else if (SH::toLowerCase(separatedCommand[0]) == "saveas") {
            if (commandArguments > 2) std::cerr << "Too much arguments for this command!\n";
            else if (commandArguments < 2) std::cerr << "Too few arguments for this command!\n";
            else {
                separatedCommand[1] = SH::strip(SH::stripBegin(separatedCommand[1],'"'),'"');
                saveas(separatedCommand[1]);
            }
        }
        else std::cerr << "Invalid command! Type 'help' to see all available commands!\n";
    }
}