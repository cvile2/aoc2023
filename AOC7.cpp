

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

struct Card {

    Card(std::string& card) {
        for(auto c : card)
            counts[c]++;
    }

    std::map<char, int> counts;
};

void process(const std::string& fn) {
    //File processing
    
    std::map<Card, long> cards;
    {
        std::fstream f{fn};
        std::string l;
        while(std::getline(f, l)) {
            cards.emplace({l.substr(0,5), 
                std::stol(l.substr(6))});
        }
    }

    int total=0;
    int rank = 1;
    for(auto& [c,stake] : cards ) {
        total+=stake*rank;
        ++rank;
    }
    std::cout << rank << std::endl;
};

int main() {
    process("AOC7_ex.txt");
    process("AOC7.txt");
    return 0;
}