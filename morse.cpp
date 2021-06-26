#include <iostream>
#include <string>
#include <locale>
#include <fstream>
#include <limits>
#include <stdlib.h>
#include <random>

// Converts an English word to Morse code
std::string morseConvert(std::string word){
    std::string morse[27] = {".-", "-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..","-....-"};
    std::string out = "";
    for(int i = 0; i < word.length(); i++){
        char letter = std::tolower(word[i]);
        int index = letter - 'a'; 
        if(letter == 45){
            out+= morse[26];
        } else if((index <= 26) && (index >= 0)) {
            out+= morse[index];
        } else {
            out+= " ";
        }
        out += "/";
    }
    return out;
}

// Goes to a line in a file, and returns the file in that state
std::fstream& goToLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; i++){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

// Return a single word from a line in a file
std::string getWordFromList(unsigned int randomNum){
    std::fstream file("words.txt");
    int lineno = randomNum;
    goToLine(file, lineno);
    std::string word;
    file >> word;
    return word;
}

// Clears the text in the terminal
void clearTerminal(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(int argc, char const *argv[]) {

    int input = -1; // Menu input variable
    std::string word;
    std::string choice;
    std::string out = "";

    std::ifstream file("words.txt");
    int numberOfLines = 0;
    std::string line;
    while (std::getline(file, line)){
        ++numberOfLines;
    }

    std::default_random_engine randEngine(time(0));
    std::uniform_int_distribution<int> dist(1, numberOfLines);

    std::cout << "\nWelcome to the Morse Code convertor \n \n";
    
    while(input != 3){
        
        out = "";

        clearTerminal();
        std::cout << "\tMAIN MENU \n \n";
        std::cout << "1)\tConvert\n";
        std::cout << "2)\tGenerate\n";
        std::cout << "3)\tQuit\n \n";

        if(!(std::cin >> input)){
            std::cin.clear();
            std::cout << "Wrong option! Need to quit... \n \n";
            input = 3;
        } else {
            switch (input){
                case 1: // Convert
                {            
                    clearTerminal();

                    std::cout << "\nWhich word would you like to convert?: ";
                    getline(std::cin.ignore(), word);

                    out = morseConvert(word);
                    std::cout << "\nThis is " + out + " in Morse! \n \n";

                    std::cout << "Main Menu? [y/n] ";
                    std::cin >> choice;
                    input = choice.compare("y") ? 3 : -1;
                }
                    break;
                case 2: // Generate
                {
                    clearTerminal();

                    std::cout << "How many words do you want to generate? " ;
                    int no_of_words = 0;
                    std::cin >> no_of_words;
                    std::cout << std::endl;

                    std::string randomWord = "";
                    std::string words[no_of_words];
                    clearTerminal();

                    for(int i = 0; i < no_of_words; i++){
                        randomWord = getWordFromList(dist(randEngine));
                        words[i] = randomWord;
                        out = morseConvert(randomWord);
                        std::cout << (i+1);
                        std::cout << ". ";
                        std::cout << out << std::endl;
                        out = "";
                        randomWord = "";
                    }
                    std::cout << std::endl;

                    std::cout << "Press ENTER to reveal the answers...";
                    std::cin.get();
                    std::cin.ignore();
                    clearTerminal();

                    for(int i = 0; i < no_of_words; i++){
                        std::cout << (i+1);
                        std::cout << ". ";
                        std::cout << words[i] << std::endl;
                    }
                    std::cout << std::endl;
                    
                    std::cout << "Main Menu? [y/n] ";
                    std::cin >> choice;
                    input = choice.compare("y") ? 3 : -1;

                    std::cout << std::endl;
                }
                    break;
                default:
                    std::cout << "Wrong option! \n \n";
                    input = -1;
            }
        }
    }
    std::cout << "Thanks for using!" << std::endl;
    return 0;
}
