#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int, char**) {
    std::vector<std::string> codes = {
        "",   "AL", "AD", "AM", "AT", "BY", "BE", "BA", "BG", "HR",
        "CY", "CZ", "DK", "EE", "FI", "FR", "GE", "DE", "GR", "HU",
        "IS", "IE", "IT", "XK", "LV", "LI", "LT", "LU", "MT", "MD",
        "MC", "ME", "NL", "MK", "NO", "PL", "PT", "RO", "RU", "SM",
        "RS", "SK", "SI", "ES", "SE", "CH", "TR", "UA", "GB", "VA"};
    std::ifstream fin("edges.txt");
    int a, b;
    std::vector<std::vector<int>> adjl(50);
    for (size_t i = 0; i < 92; i++) {
        fin >> a >> b;
        adjl[a].push_back(b);
        adjl[b].push_back(a);
    }
    std::ofstream fout("../../adjl.txt");
    for (size_t i = 1; i < 50; i++) {
        for (size_t j = 0; j < adjl[i].size(); j++) {
            fout << adjl[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
    fout.open("../../adjlv2.txt");
    for (size_t i = 1; i < 50; i++) {
        fout << i << '\t';
        for (size_t j = 0; j < adjl[i].size(); j++) {
            fout << adjl[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
    fout.open("../../adjm.txt");
    int deg_sum = 0;
    std::vector<std::vector<int>> adjm(49, std::vector<int>(49, 0));
    for (size_t i = 0; i < 49; i++) {
        for (size_t j = 0; j < adjl[i + 1].size(); j++) {
            adjm[i][adjl[i + 1][j] - 1] = 1;
            ++deg_sum;
        }
    }
    for (size_t i = 0; i < 49; i++) {
        for (size_t j = 0; j < 49; j++) {
            fout << adjm[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.open("../../data.txt");
    fout << "Sum of degrees: " << deg_sum << '\n';
    fout << "Number of edges: " << deg_sum / 2 << '\n';
    return 0;
}