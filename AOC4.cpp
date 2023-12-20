
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <optional>

void process(const std::string& fn, int num_winners, int num_tries, int card_max ) {
    //File processing
    std::vector<std::set<int>> winners;
    std::vector<std::set<int>> numbers;
    {
        std::fstream f{fn};
        std::string l;
        while(std::getline(f, l)) {
            int pos = 5;
            int card = stoi(l.substr(pos, 3));
                std::cout << "card " << card << ": ";
            winners.push_back({});
            numbers.push_back({});
            pos+=2 + card_max;
            for(int i = 0; i < num_winners; ++i, pos+=3) {
                auto num = l.substr(pos, 2);
                std::cout << num << " ";
                winners.back().insert(stoi(num));
            }
            pos+=2;
            std::cout << "|";
            for(int i = 0; i < num_tries; ++i, pos+=3) {
                auto num = l.substr(pos, 2);
                std::cout << num << " ";
                numbers.back().insert(stoi(num));
            }
            pos+=3;
            std::cout << std::endl;
        }
    }
    int cardcount = (int)numbers.size();
    //total scores
    int total = 0;
    for(auto n = 0 ; n < cardcount; ++n) {
        int score = 0;
        for(auto w : winners[n]) {
            if (numbers[n].find(w)!=numbers[n].end()) 
                score = (score == 0 ? 1 : score * 2 );
        }
        //std::cout << n+1 << ":" << score << std::endl;
        total += score;
    }
    std::cout << "Part 1 total=" << total << std::endl;

    //total scores
    int totalcards = 0;
    std::vector<int> cards(cardcount, 1);  
    for(auto n = 0 ; n < cardcount; ++n) {
        int wiinercount = 0;
        for(auto w : winners[n]) {
            if (numbers[n].find(w)!=numbers[n].end()) {
                ++wiinercount;
            }
        }
        for(int x = 1; x<=wiinercount; ++x) {
            if(x+n < cardcount) 
                cards[x+n] += cards[n];
        }
        //std::cout << n+1 << ": cards=" <<  cards[n]  << " winners=" << wiinercount << std::endl;
        totalcards += (cards[n]);
    }
    std::cout << "Part 2 cards=" << totalcards << std::endl;
}
int main() {
    process("AOC4_ex.txt", 5, 8, 1);
    process("AOC4.txt", 10, 25, 3);
    return 0;
}