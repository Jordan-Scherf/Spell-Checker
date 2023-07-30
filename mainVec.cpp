/*
Name: Jordan Scherf (NSHE: 5005736913)
Class and Assignment #: CS 302 Assignment 5
Program Description: This Program is essentially a spellchecker program that takes in
 a dictionary to be placed into a vector then reads in another file to spell check it then offer
 suggestions for other words if they are not found in the dictionary using string manipulation
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <time.h>
int main() {
    clock_t tStart = clock();
    // Creating dictionary Hashmap
    std::vector<std::string> dictionary;
    // Creating a Vector of the Misspelled Words
    std::vector<std::string> misspelled;
    // Creating a Vector of the Suggested Words
    std::vector<std::string> suggestions;
    // Strings for checking words and getting the name for the input file
    std::string Wordcheck;
    std::string inputfile;

    // Opening the Dictionary
    std::ifstream file("usa.txt");
    if(!file.is_open()){
        std::cout << "Error opening File\n";
        return 1;
    }
    std::cout << '\n';

    // Taking in each word and capatilizing them then placing them into the vector
    std::string word;
    while(file >> word){
        for (auto& c : word) {
            c = std::toupper(c);
        }
        dictionary.push_back(word);
    }
    file.close();

    std::cout << "Enter filename:";
    std::cin >> inputfile;
    std::cout << '\n';
    std::ifstream inputfilename(inputfile);
    if(!inputfilename.is_open()){
        std::cout << "Error opening Input File\n";
        return 1;
    }

    // getting each word then captilizing them
    bool check = false;
    while(inputfilename >> word) {
        check = false;
        for (auto &c: word) {
            c = std::toupper(c);
        }

        // checking if the word is in the dictionary
        // if not, place in misspelled vector
        for (auto it3 = dictionary.begin(); it3 != dictionary.end(); it3++) {
            if (*it3  == word){
                check = true;
            }

        }
        if (check == false) {
            auto it = std::find(misspelled.begin(), misspelled.end(), word);
            if (it == misspelled.end())
                misspelled.push_back(word);
        }
    }
/*
    std::cout << "These Words are not in the Dictionary: \n";

    for (auto it = misspelled.begin(); it != misspelled.end(); it++){
        std::cout << *it << '\n';
    }

*/
/*Essentially each word is placed into an iterator that first changes each letter into another
     * letter to check if that can be found in the dictionary and if it is, it is placed
     * into the suggestions vector. Otherwise it places letter between and at the ends of the word
     * Thus creating a new word to check in the dictionary and if it is found, it is placed in the suggestions vector */
    for( auto it = misspelled.begin(); it != misspelled.end(); it++) {
        std::cout << *it << " is misspelled\n" << '\n';
        Wordcheck = *it;
        // This is checking for one offs
        for (int i = Wordcheck.length()-1; i >= 0; i--) {
            Wordcheck = *it;
            for (char j = 'A'; j != 'Z' + 1; j++) {
                Wordcheck.at(i) = j;
                auto it4 = std::find(dictionary.begin(), dictionary.end(), Wordcheck);
                if(it4 != dictionary.end()){
                    suggestions.push_back(Wordcheck);
                }
            }
        }
        std::string Wordcheck2 = *it;
        // Lets check the word with Character Insertion

        for (int i = 0; i != Wordcheck2.length() + 1; i++){
            Wordcheck = *it;
            for (char j = 'A'; j != 'Z' + 1; j++) {
                Wordcheck = *it;
                std::string tmp(1, j);
                Wordcheck.insert(i, tmp);
                auto it4 = std::find(dictionary.begin(), dictionary.end(), Wordcheck);
                if(it4 != dictionary.end()){
                    suggestions.push_back(Wordcheck);
                }
            }
        }
        // Checks to see if the suggestions vector is empty if it isnt
        // then it outputs all the suggested words in the vector
        if(suggestions.empty()){
            std::cout << "No suggestions\n\n";

        }else{
            std::sort(suggestions.begin(), suggestions.end());
            std::cout << "Suggested words\n";
            for (auto it2 = suggestions.begin(); it2 != suggestions.end(); it2++){
                std::cout << *it2 << '\n';
            }
            std::cout << '\n';
        }
        // Clears it for the next round of word checking
        suggestions.clear();
    }
    std::cout << "time taken = " << (clock() - tStart);
    return 0;
}
