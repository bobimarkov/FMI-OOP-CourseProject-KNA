#include "Helpers/StringHelper.hpp"
#include "Automaton.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define SH StringHelper

bool openedFile = false;
std::string openedFilePath;
std::string fileName;

std::vector<Automaton> automatons;

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
            automatons.push_back(a);
        }

        std::cout << "Successfully opened " << fileName << "!\n";
        in.close();
    }
    else std::cerr << "There is already an opened file! You can close the file with 'close'\n"; 
}

void close() {
    if(openedFile) {
        openedFile = false;
        automatons.clear();
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

        for(Automaton s: automatons) {
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

}

void print (int id) {

}

void save (int id, std::string path) {

}

void empty (int id) {

}

void deterministic (int id) {

}

void recognize  (int id, std::string word) {

}
 
void _union (int id1, int id2) {

}

void concat (int id1, int id2) {

} 

void un (int id) {

}

void reg (std::string regex) {
    
}

int main () {
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