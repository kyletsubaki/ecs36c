#include "teamdata.h"

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