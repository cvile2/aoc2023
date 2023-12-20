
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <optional>
const std::vector<std::vector<int>> directions = {{0,1},{1,1},{1,0},
                         {0,-1},{-1,-1},{-1,0},
                         {-1,1}, {1,-1} };

struct Loc {
    Loc(int x, int y) : i(x), j(y) {};
    int i;
    int j;
    bool operator==(const Loc& r) const noexcept {
        return i == r.i &&  j == r.j;
    }
};
struct LocHash {
    size_t operator()(const Loc& p) const
    {
        return p.j * 1000000 + p.i;
    }
};

void aoc2_part1(std::string fn) {
    //File processing
    std::vector<std::string> grid;
    {
        std::fstream f{fn};
        std::string l;
        while(std::getline(f, l)) 
            grid.push_back(l);        
    }
    
    //part1 tracking
    int total = 0;
    bool matchSymbol = false;
    int num = 0;

    //part2 tracking
    std::unordered_map<Loc, std::vector<int>, LocHash> gear_nums;
    std::optional<Loc> gear;

    //Data processing
    for (int j = 0; j < grid.size(); j++) {
        auto& line = grid[j];
        for (int i = 0; i<line.size(); i++) {

            char c = line[i];
            if(isdigit(c)) {
                if (num != 0)
                    num *= 10;
                
                num += (c - '0');
                
                for(auto& d : directions) {
                    int i2 = i + d[0];
                    int j2 = j + d[1];
                    if(i2>0 && j2>0 && i2<grid[0].size() && j2<grid.size()) {
                        char c2 = grid[j2][i2];
                        matchSymbol = matchSymbol || (c2 != '.' && !isdigit(c2));

                        if(!gear.has_value() && c2 == '*') {
                            gear = Loc{i2, j2};
                        }
                    }
                }
            }
            //finished processing current number or line
            if(!isdigit(c) || i == line.size()-1) {
                if (matchSymbol) {
                    total += num;
                    if(gear.has_value())  {
                        gear_nums[*gear].push_back(num);
                    }
                }
                matchSymbol = false;
                num = 0;
                gear.reset();
            }
        }
    }
    int gearNum = 0;
    for(auto&[k,v]:gear_nums) {
        if (v.size()==2)
            gearNum += v[0]*v[1];
    }
    std::cout << "P1: " << total << " P2: "<< gearNum << std::endl;
}

int main() {
    aoc2_part1("AOC3_ex.txt");
    aoc2_part1("AOC3.txt");
}