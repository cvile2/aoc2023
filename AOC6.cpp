

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

std::vector<long long> tokenize(const std::string& str) {
    std::vector<long long> toks;

    for(size_t pos = 0; pos<str.size(); ) {
        pos = str.find_first_not_of(" ", pos);
        auto end = str.find_first_of(" ", pos);
        end = (end == std::string::npos) ? str.size() : end;
        toks.push_back(std::stoll(str.substr(pos, end-pos)));
        pos = end+1;
    }
    return toks;
}

long long parse_nospace(const std::string& str) {
    std::string res;

    for(auto pos = 0; pos<(int)str.size(); ) {
        pos = str.find_first_not_of(" ", pos);
        auto end = str.find_first_of(" ", pos);
        end = (end == std::string::npos) ? str.size() : end;
        res += str.substr(pos, end-pos);
        pos = end+1;
    }
    return std::stoll(res);
}

auto race(const std::vector<long long> race_time, 
    const std::vector<long long> record_distance) {
    auto total = 1;
    for(auto race = 0; race<(long)race_time.size(); ++race) {
        auto count = 0;
        for(auto hold = 1; hold < race_time[race]-1; ++hold) {

            auto distance = race_time[race] - hold;
            auto travelled = distance * hold;
            if (travelled > record_distance[race]) {
                count++;
            }
        }
        total *= count;
    }
    return total;
}

void process(const std::string& fn) {
    //File processing
    std::vector<long long> race_time;
    std::vector<long long> record_distance;
    long long race_time2;
    long long record_distance2;
    {
        std::fstream f{fn};
        std::string race, dist;
        std::getline(f, race);
        std::getline(f, dist);
        race_time = tokenize(race.substr(11));
        record_distance = tokenize(dist.substr(11));

        race_time2 = parse_nospace(race.substr(11));
        record_distance2  = parse_nospace(dist.substr(11));
    }

    auto total = race(race_time, record_distance);
    auto total2 = race({race_time2}, { record_distance2});

    std::cout << "total=" << total << " " << total2 << std::endl;
};

int main() {
    process("AOC6_ex.txt");
    process("AOC6.txt");
    return 0;
}