#include <iostream>
#include <tuple>
#include"Dictionary.hpp"

std::vector<std::tuple<std::string, std::string>> readStartTargetWords(const std::string &inputFileName) {
    std::ifstream ladderStream;
    ladderStream.open(inputFileName, std::ios_base::in);
    if( ! ladderStream.is_open()) {
        std::cout << "Unable to open the input file ->" << inputFileName << "<- that contains pairs of words.\n";
        exit(2);
    }
    std::cout << "Successfully opened " << inputFileName << std::endl;
    std::vector<std::tuple<std::string, std::string>> startTargetVector;

    // while there are input lines, do:
    //     read the pair of words into variables, word1, word2
    //     startTargetVector.push_back(make_tuple(word1, word2));
    // end-while
    std::string word1, word2;
    while(ladderStream >> word1 >> word2) {
        startTargetVector.push_back(std::make_tuple(word1, word2));
    }

    // Just so you see how this works, let's add two arbitrary words.
    std::string bell = "bell", ball = "ball";
    startTargetVector.push_back(std::make_tuple(bell, ball));
    return startTargetVector;
}

int main(int argc, char *argv[]) { // the main function.
    if( argc != 3 ) {
        std::cout << "usage: " << argv[0] << " inputFileNameThatContainsDictionary inputFileNameThatContainsPairsOfWords\n";
        exit(1);
    }

    std::ifstream dictionaryStream;
    dictionaryStream.open(argv[1], std::ios_base::in);
    if( ! dictionaryStream.is_open()) {
        std::cout << "Unable to open input file ->" << argv[1] << "<-\n";
        exit(2);
    }
    std::cout << "Successfully opened " << argv[1] << std::endl;
    // we just wanted to make sure that the input file exists. So, close it
    // and let the instance of Dictionary open and use it.
//    std::string word;
//    while(dictionaryStream >> word) {
//        std::cout << word << std::endl;
//    }
    dictionaryStream.close();

    Dictionary dictionary(argv[1]);
    auto arrayOfPairsToBuildLadders = readStartTargetWords(argv[2]);
    for(const auto & [startWord, targetWord]: arrayOfPairsToBuildLadders) {
        std::cout << "start word is " << startWord << "; target word is " << targetWord << std::endl;
    }

//    std::cout << "size of dictionary is " << dictionary.size() << std::endl;
//
//    std::string item = "bell";
//    std::string itemN = "callFSFD";
//    int mem = dictionary.member(itemN);
//    std::cout <<"\n" << item << " is " << mem << "\n " <<std::endl;


//    Dictionary dictionary(argv[1]);

    std::string aRandomWord = "fake";
    auto neighbors = dictionary.neighborsOf(aRandomWord);
    std::cout << "\nNeighbors of " << aRandomWord << " are" << std::endl;
    for( auto neighbor: neighbors )
        std::cout << neighbor << std::endl;





//    for(const auto & [startWord, targetWord]:arrayOfPairsToBuildLadders) {
//        std::vector<std::string> paths = dictionary.pathFromTo(startWord, targetWord);
//        if (paths.size() == 0) {
//            std::cout << "There is no path from " << startWord << " to " << targetWord << "\n" << std::endl;
//        } else {
//        std::cout << "A ladder from " << startWord << " to " << targetWord << " is:" << std::endl;
//        for (const auto &path: paths) {
//            std::cout << path << std::endl;
//        }
//        std::cout << std::endl;
//    }
//
//    }
//

    return 0;
}