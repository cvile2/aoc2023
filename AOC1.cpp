#include <iostream>
#include <fstream>
#include <unordered_map>

int part1() {

    auto f = std::ifstream{"./AOC1_input.txt"};
    std::string s;
    int total = 0;
    while(std::getline(f,s)) {
        for (int l = 0;;l++) {
            if(std::isdigit(s[l])) {
                total += (s[l] - '0') * 10;
                break;
            }
        }
         for (int r = s.size()-1;;--r) {
            if(std::isdigit(s[r])) {
                total += s[r] - '0';
                break;
            }
        }     
    }
    return total;
}

const std::unordered_map<std::string,int> numstrs = {
   { "one", 1 },   { "two",  2 },   { "three",  3 },   { "four", 4 },
   { "five",  5 },   { "six",  6 },   { "seven", 7 },   { "eight", 8 },
   { "nine", 9 }
};

int match(const std::string& s, const int offset) {
    if(std::isdigit(s[offset])) 
        return (s[offset] - '0');
    
    for (const auto& [k,v] : numstrs) {
        if(k == s.substr(offset, k.size())) {
            return v;
        }
    }
    return 0;
}

int part2() {
    auto f = std::ifstream{"./AOC1_input.txt"};
    std::string s;
    int total = 0;
    while(std::getline(f,s)) {
        for (int l = 0;;l++) {
            int m = match(s,l);
            if (m!=0) {
                total += m * 10;
                break;
            }
        }
        for (int r = s.size()-1;;--r) {
            int m = match(s,r);
            if (m!=0) {
                total += m;
                break;
            }
        }     
    }
    return total;
}

int main() {
    std::cout << part1()<< std::endl;
    std::cout << part2()<< std::endl;
    return 0;
}