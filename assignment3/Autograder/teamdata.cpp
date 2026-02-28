#include "teamdata.h"

TeamData::TeamData(std::string filename) {
    std::ifstream in(filename); // Open file
    if (!in) {
        std::cerr << "Error: Could not open file." << std::endl; // Error if file can't open
        exit(1); // End
    }

    nlohmann::json json; // Declare JSON object
    in >> json; // Parse the file 
    numPlayers_ = json["metadata"]["numPlayers"]; // Extract number of players from metadata and store in numPlayers

    // Initialize numPlayers by numPlayers matrix with 0.0 for every entry
    winPercentages_ = std::vector(numPlayers_, std::vector(numPlayers_, 0.0));

    // Fill matrix from teamStats
    for (const auto& entry : json["teamStats"]) {
        int p1 = entry["playerOne"]; // First player's index from JSON entry
        int p2 = entry["playerTwo"]; // Second player's index from JSON entry
        double winPct = entry["winPercentage"].get<double>() / 100.0; // Convert from percent to probability
        winPercentages_[p1][p2] = winPct; // Store probability that player p1 beats player p2
        winPercentages_[p2][p1] = 1.0 - winPct; // Store probability for reverse matchup
    }
}

int TeamData::numPlayers() const {
    return numPlayers_; // Return the total number of players stored in the object
}