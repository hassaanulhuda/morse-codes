#include <iostream>
#include <string>
#include <locale>
#include <fstream>
#include <limits>
#include <stdlib.h>
#include <windows.h>

std::string morseConvert(std::string letter){
    std::string alphabet[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    std::string morse[26] = {".-", "-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
    for (int i = 0; i < 26; i++){
        if(letter.compare(alphabet[i]) == 0){
            return morse[i];
        } else if (letter.compare(" ") == 0){
            return " ";
        }
    }
    return " ";
}

std::fstream& goToLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; i++){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}


std::string generateRandomWord(unsigned int num){
    std::fstream file("words.txt");
    int lineno = rand() % num + 1;
    goToLine(file, lineno);
    std::string word;
    file >> word;
    return word;
}

int main(int argc, char const *argv[]) {

    int input = -1;
    std::string word;
    std::string choice;
    std::string out = "";
    std::locale loc;

    srand((unsigned)time(NULL));

    std::ifstream file("words.txt");
    int number_of_lines = 0;
    std::string line;
    while (std::getline(file, line)){
        ++number_of_lines;
    }

    std::cout << "\nWelcome to the Morse Code convertor \n \n";
    
    while(input != 3){
        
        system("clear");
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
                case 1:
                {            
                    system("clear");
                    std::cout << "\nWhich word would you like to convert?: ";
                    getline(std::cin.ignore(), word);
                    for(int i = 0; i < word.length(); i++){
                        std::string letter = std::string(1, std::tolower(word[i], loc));
                        out += morseConvert(letter) + "/";
                    }
                    std::cout << "\nThis is " + out + " in Morse! \n \n";
                    std::cout << "Main Menu? [y/n] ";
                    std::cin >> choice;
                    if(choice.compare("y")){
                        input = 3;
                    } else {
                        input = -1;
                    }
                }
                    break;
                case 2:
                {
                    system("clear");
                    std::cout << "How many words do you want to generate? " ;
                    int no_of_words = 0;
                    std::string randomWord = "";
                    std::cin >> no_of_words;
                    std::string words[no_of_words];
                    std::cout << std::endl;
                    system("clear");
                    for(int i = 0; i < no_of_words; i++){
                        randomWord = generateRandomWord(number_of_lines);
                        words[i] = randomWord;
                        // std::cout << "chosen word: " + randomWord << std::endl;
                        for(int i = 0; i < randomWord.length(); i++){
                            std::string letter = std::string(1, std::tolower(randomWord[i], loc));
                            out += morseConvert(letter) + "/";
                        }
                        std::cout << (i+1);
                        std::cout << ". ";
                        std::cout << out << std::endl;
                        out = "";
                        randomWord = "";
                    }
                    std::cout << std::endl;
                    std::cout << "Type any letter and press enter to reveal answers ";
                    std::cin >> word;
                    system("clear");
                    for(int i = 0; i < no_of_words; i++){
                        std::cout << (i+1);
                        std::cout << ". ";
                        std::cout << words[i] << std::endl;
                    }
                    std::cout << std::endl;
                    std::cout << "Main Menu? [y/n] ";
                    std::cin >> choice;
                    if(choice.compare("y")){
                        input = 3;
                    } else {
                        input = -1;
                    }         
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
