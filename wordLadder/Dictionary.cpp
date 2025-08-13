//
// Created by Ali Kooshesh on 8/22/23.
//

#include "Dictionary.hpp"

#include <iostream>
#include <fstream>
#include <tuple>
#include "Dictionary.hpp"

Dictionary::Dictionary(std::string inputFileName) {
    // open inputFileName and store its contents, which is a collection of
    // words, one per line, in vector, "words".
    std::ifstream dictionaryStream;
    dictionaryStream.open(inputFileName, std::ios_base::in);
    while(dictionaryStream >> inputFileName) {
        words.push_back(inputFileName);
        used.push_back(false);
    }
    std::cout << "Creating an instance of Dictionary with input file: " << inputFileName << std::endl;
    dictionaryStream.close();

//    resetPath();
//    int pdof = positionalDiff("bell", "bowling");
//    std::cout << "\n" << pdof << std::endl;
//
//    std::string name = "lake";
//    int idx = idxOfSuccessorWordFrom(name, member(name));
//    if( idx == size() ) {
//        std::cout << "there was not a successor word for "<< name << " starting with " << words[member(name)] <<" \n"<< std::endl;
//    } else {
//        std::cout <<words[idx] << " is a successor for " << name<< "\n " <<std::endl;
//    }

    printDictionary();
    std::cout << "\n" << std::endl;
    printLadder();

}

Dictionary::~Dictionary() {
    // close the input stream if it was successfully opened.
    if(dictionaryStream.is_open())
        dictionaryStream.close();
}

int Dictionary::size() {
    return words.size();
}

void Dictionary::resetPath() {
    for(int i = 0; i < used.size(); i++) {
        used.at(i) = false;
    }
}

int Dictionary::member(std::string word) {
    for(int i = 0; i < words.size(); i++) {
        if(words.at(i) == word) {
            return i;
        }
    }
    return words.size();
}

int Dictionary::positionalDiff(std::string word1, std::string word2) {
    int diff = 0;
    for(int i = 0; i < word1.size(); i++) {
        if(word1.at(i) != word2.at(i)) {
            diff++;
        }
    }
    return diff;
}

int Dictionary::idxOfSuccessorWordFrom(std::string word, int fromIdx) {
    for(int i = fromIdx; i < words.size(); i++) {
        if(positionalDiff(words.at(i), word) == 1 && used.at(i) == false)
            return i;
        else
            continue;
    }
    return size();
}



//works but for fate and kate
std::vector<std::string> Dictionary::pathFromTo(std::string from, std::string to) {
    std::vector<std::string> path;
    std::stack< std::tuple<std::string, int> > ladder;
    int popWordIdx = 0;
    ladder.push(std::make_tuple(from, member(from)));
    path.push_back(from);
    resetPath();
    used[member(from)] = true;

    while (!ladder.empty()) {
        auto [topWord, topWordIdx] = ladder.top();
        int successorIdx = idxOfSuccessorWordFrom(topWord, 0);
        if( successorIdx == size()) {
            popWordIdx = successorIdx;
            ladder.pop();
            path.pop_back();
            if(ladder.empty()) {
                return path;
            }
            auto [curTopWord, topWordIdx] = ladder.top();
            if(idxOfSuccessorWordFrom(curTopWord, member(topWord))== size()) {
                ladder.pop();
                path.pop_back();
            }
            else {
                continue;
            }
        }
        else{
            ladder.push(std::make_tuple(words.at(successorIdx), successorIdx));
            path.push_back(words.at(successorIdx));
            used[successorIdx] = true;
            if(words.at(successorIdx) == to) {
                return path;
            }
        }
    }
    return path;
}


std::vector<std::string> Dictionary::neighborsOf(std::string someWord) {
    std::vector<std::string> neighbors;
    for(int i = 0; i < words.size(); i++) {
        if(positionalDiff(someWord, words.at(i)) == 1) {
            neighbors.push_back(words.at(i));
        }
    }
    return neighbors;
}


void Dictionary::printDictionary() {
    // print the contents of "words"
    for(int i = 0; i < words.size(); i++) {
        std::cout << words.at(i) << std::endl;
    }
}

void Dictionary::printLadder() {
    // print the contents of "ladder"
    std::string inputFileName = "ladder_start_target_pairs.txt";
    std::ifstream docStream;
    docStream.open(inputFileName);
    std::string startWord, targetWord;
    while(!docStream.eof()) {
        docStream >> startWord >> targetWord;

        std::vector<std::string> paths = pathFromTo(startWord, targetWord);
        if (paths.size() == 0) {
            std::cout << "No ladder for the pair " << startWord << " and " << targetWord << " exists.\n" << std::endl;
        } else {
            std::cout << "A ladder from " << startWord << " to " << targetWord << " is:" << std::endl;
            for (const auto &path: paths) {
                std::cout << path << std::endl;
            }
            std::cout << std::endl;
        }
    }
}
