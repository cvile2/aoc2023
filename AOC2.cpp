
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>

auto aoc2_part1(std::string fn) {
    int possibles = 0;
    int powerset = 0;

    std::fstream file{fn};
    std::string line;
    int id = 0;
    while(std::getline(file, line)) {
        ++id;
        auto pos = line.find_first_of(":", 0) + 2; 

        std::map<char, int> max_ct;
        std::map<char, int> ct;
        bool good = true;
        while(1) {
            auto edn = line.find_first_of(" ", pos) ;

            int num = std::stoi(line.substr(pos, edn-pos));
            char c = line[edn+1];
            ct[c]=num;
            max_ct[c]=std::max(max_ct[c], num);
            auto ede = line.find_first_of(" ", edn+1); 
            if( ede==std::string::npos || line[ede-1] == ';') {
                if(ct['r'] > 12 || ct['g'] > 13 || ct['b'] > 14 ) 
                    good = false;
                ct = {};
            }
            pos = ede + 1; 
            if (ede==std::string::npos) break;
        }   
        if(good) 
            possibles+=id;
        powerset += (max_ct['r'] * max_ct['g'] * max_ct['b']);
        
    }
    return std::vector{possibles, powerset};
}

int main() {
    auto ans = aoc2_part1("AOC2.txt");
    std::cout << "Part 1=" << ans[0] << ", Part 2=" << ans[1] << std::endl;
}