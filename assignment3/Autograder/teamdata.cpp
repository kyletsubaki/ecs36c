#include "teamdata.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

TeamData::TeamData(std::string filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Error: Could not open file." << std::endl;
        exit(1);
    }

    nlohmann::json json;
    in >> json;
    numPlayers_ = json["metadata"]["numPlayers"]; // Read number of players
    winPercentages_ = std::vector<std::vector<double>>(numPlayers_, std::vector<double>(numPlayers_, 0.0));

    // Fill matrix from teamStats
    for (const auto& entry : json["teamStats"]) {
        int p1 = entry["playerOne"];
        int p2 = entry["playerTwo"];
        double winPct = entry["winPercentage"].get<double>() / 100.0;
        winPercentages_[p1][p2] = winPct;
        winPercentages_[p2][p1] = 1.0 - winPct;
    }
}

int TeamData::numPlayers() const {
    return numPlayers_;
}

int main(int argc, char** argv) {
    TeamData data(argv[1]);
    int totalPlayers = data.numPlayers();
    std::vector<bool> used(totalPlayers, false);
    std::vector<std::vector<int>> teams;
    size_t teamsNeeded = totalPlayers / 2;
    while (teams.size() < teamsNeeded) {
        double bestDiff = 1.0;
        int bestI = -1;
        int bestJ = -1;
        for (int i = 0; i < totalPlayers; ++i) {
            if (used[i]) continue;
            for (int j = i + 1; j < totalPlayers; ++j) {
                if (used[j]) continue;
                double winProb = data.winPercentages(i, j);
                double diff = std::abs(winProb - 0.5);
                if (diff < bestDiff) {
                    bestDiff = diff;
                    bestI = i;
                    bestJ = j;
                }
            }
        }
        teams.push_back({bestI, bestJ});
        used[bestI] = true;
        used[bestJ] = true;
    }
    nlohmann::json output;
    output["teams"] = teams;
    std::cout << output.dump(2) << std::endl;
}