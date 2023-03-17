#include <algorithm>
#include <cstdint>
#include <fstream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

std::vector<uint32_t> distance(const std::vector<std::vector<uint8_t>>& adj,
                               uint32_t start) {
    std::queue<uint32_t> q;
    std::vector<uint32_t> dist(adj.size(),
                               std::numeric_limits<uint32_t>::max());
    dist[start] = 0;
    q.push(start);
    uint32_t index;
    while (!q.empty()) {
        index = q.front();
        for (uint32_t i = 0; i < adj.size(); i++) {
            if (adj[index][i] == '0' ||
                dist[i] != std::numeric_limits<uint32_t>::max()) {
                continue;
            }
            q.push(i);
            dist[i] = dist[index] + 1;
        }
        q.pop();
    }
    return dist;
}

int main() {
    std::ifstream fin("../../adjm.txt");
    std::ofstream fout("../../eccentricity.txt");
    std::vector<std::vector<uint8_t>> adjm(44, std::vector<uint8_t>(44));
    for (size_t i = 0; i < 44; i++) {
        for (size_t j = 0; j < 44; j++) {
            fin >> adjm[i][j];
        }
    }
    std::vector<uint32_t> ecc(44);
    std::vector<uint32_t> temp;
    for (uint32_t i = 0; i < 44; i++) {
        temp = distance(adjm, i);
        ecc[i] = *std::max_element(temp.begin(), temp.end());
    }

    uint32_t radius = *std::min_element(ecc.begin(), ecc.end());
    uint32_t diameter = *std::max_element(ecc.begin(), ecc.end());
    fout << "Radius: " << radius << '\n';
    fout << "Diameter: " << diameter << '\n';
    fout << "Center vertices: ";
    for (uint32_t i = 0; i < ecc.size(); i++) {
        if (ecc[i] == radius) {
            fout << i + 1 << ' ';
        }
    }
    fout << '\n';
    for (uint32_t i = 0; i < 44; i++) {
        fout << i + 1 << ": " << ecc[i] << '\n';
    }
    return 0;
}
