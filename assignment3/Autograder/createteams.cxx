#include "teamdata.h"

int main(int argc, char** argv) {
    TeamData data(argv[1]); // Create TeamData object using input file
    int totalPlayers = data.numPlayers(); // Get total number of players 
    std::vector<bool> used(totalPlayers, false); // Track whether each player has already been assigned to a team
    std::vector<std::pair<int,int>> teams; // Store the resulting teams as pairs of player indices
    size_t teamsNeeded = totalPlayers / 2; // Store number of 2 person teams that must be formed

    while (teams.size() < teamsNeeded) {
        double bestDiff = 1.0; // Initialize smallest difference from 50% found so far
        int bestI = -1; // Store index of first player in best pair
        int bestJ = -1; // Store index of second player in best pair

        for (int i = 0; i < totalPlayers; ++i) {
            if (used[i]) continue; // Skip player i if already assigned to a team
            for (int j = i + 1; j < totalPlayers; ++j) {
                if (used[j]) continue; // Skip player j if already assigned to a team
                double winProb = data.winPercentages(i, j); // Get probability that player i beats player j
                double diff = std::abs(winProb - 0.5); // Compute how far this probability is from 50%
                if (diff < bestDiff) {
                    bestDiff = diff; // Update smallest difference found
                    bestI = i; // Record best first player index
                    bestJ = j; // Record best second player index
                }
            }
        }
        teams.emplace_back(bestI, bestJ); // Add the best pair found to the teams list
        used[bestI] = true; // Mark first player as assigned
        used[bestJ] = true; // Mark second player as assigned
    }
    nlohmann::json output; // Create output JSON
    output["teams"] = teams; // Store teams vector in teams key
    std::cout << output.dump(2) << std::endl; // Print JSON 
}