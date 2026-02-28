#include "teamdata.h"

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