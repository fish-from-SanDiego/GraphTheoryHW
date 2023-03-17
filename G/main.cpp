#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

int main(int, char**) {
    std::vector<std::string> colors = {"",       "orange", "cyan", "green",
                                       "yellow", "black",  "red",  "magenta",
                                       "blue",   "purple"};
    std::vector<std::string> codes = {
        "",   "AL", "AD", "AM", "AT", "BY", "BE", "BA", "BG", "HR", "CZ", "DK",
        "EE", "FI", "FR", "GE", "DE", "GR", "HU", "IT", "XK", "LV", "LI", "LT",
        "LU", "MD", "MC", "ME", "NL", "MK", "NO", "PL", "PT", "RO", "RU", "SM",
        "RS", "SK", "SI", "ES", "SE", "CH", "TR", "UA", "VA"};
    std::ifstream fin("../../edges.txt");
    std::vector<int> order;
    std::vector<std::pair<int, int>> edges_order;
    int a, b, c;
    std::vector<std::vector<int>> adjl(45);
    for (size_t i = 0; i < 91; i++) {
        fin >> a >> b;
        adjl[a].push_back(b);
        adjl[b].push_back(a);
        edges_order.push_back(std::make_pair(a, b));
        if (std::find(order.begin(), order.end(), a) == order.end()) {
            order.push_back(a);
        }
        if (std::find(order.begin(), order.end(), b) == order.end()) {
            order.push_back(b);
        }
    }
    std::ofstream fout("../../adjl.txt");
    for (size_t i = 1; i < 45; i++) {
        for (size_t j = 0; j < adjl[i].size(); j++) {
            fout << adjl[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
    fout.open("../../adjlv2.txt");
    for (size_t i = 1; i < 45; i++) {
        fout << i << '\t';
        for (size_t j = 0; j < adjl[i].size(); j++) {
            fout << adjl[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
    fout.open("../../adjm.txt");
    int deg_sum = 0;
    std::vector<std::vector<int>> adjm(44, std::vector<int>(44, 0));
    for (size_t i = 0; i < 44; i++) {
        for (size_t j = 0; j < adjl[i + 1].size(); j++) {
            adjm[i][adjl[i + 1][j] - 1] = 1;
            ++deg_sum;
        }
    }
    for (size_t i = 0; i < 44; i++) {
        for (size_t j = 0; j < 44; j++) {
            fout << adjm[i][j] << ' ';
        }
        fout << '\n';
    }
    fout.close();
    fout.open("../../data.txt");
    fout << "Sum of degrees: " << deg_sum << '\n';
    fout << "Number of edges: " << deg_sum / 2 << '\n';

    fin.close();
    fout.close();

    fin.open("../../colors.txt");
    fout.open("../../coloring.txt");
    std::map<int, int> coloring;
    for (size_t i = 0; i < 44; i++) {
        fin >> a >> b;
        coloring[a] = b;
    }

    for (size_t i = 0; i < order.size(); i++) {
        fout << "\"" << order[i] << "(" << codes[order[i]] << ")\"[color = \""
             << colors[coloring[order[i]]] << "\"]\n";
    }
    fin.close();
    fout.close();

    fin.open("../../edge colors.txt");
    fout.open("../../edge coloring.txt");
    std::map<std::pair<int, int>, int> edges_coloring;
    for (size_t i = 0; i < 91; i++) {
        fin >> a >> b >> c;
        edges_coloring[std::make_pair(a, b)] = c;
    }
    for (size_t i = 0; i < 91; i++) {
        c = edges_coloring[edges_order[i]];
        fout << "\"" << edges_order[i].first << "("
             << codes[edges_order[i].first] << ")\" -- "
             << "\"" << edges_order[i].second << "("
             << codes[edges_order[i].second] << ")\"[color = \"" << colors[c]
             << "\"]\n";
    }

    fin.close();
    fout.close();

    fin.open("../../stable set.txt");
    fout.open("../../stable set graphviz.txt");
    std::vector<int> stable(19);
    for (size_t i = 0; i < 19; i++) {
        fin >> stable[i];
    }
    for (size_t i = 0; i < order.size(); i++) {
        fout << "\"" << order[i] << "(" << codes[order[i]] << ")\"";
        if (std::find(stable.begin(), stable.end(), order[i]) != stable.end()) {
            fout << "[color = \"" << colors[1] << "\"]\n";
        } else {
            fout << "\n";
        }
    }

    fin.close();
    fout.close();

    fin.open("../../matching.txt");
    fout.open("../../matching colored.txt");
    std::set<std::pair<int, int>> matching;
    for (size_t i = 0; i < 20; i++) {
        fin >> a >> b;
        matching.insert(std::make_pair(a, b));
    }
    for (size_t i = 0; i < 91; i++) {
        fout << "\"" << edges_order[i].first << "("
             << codes[edges_order[i].first] << ")\" -- "
             << "\"" << edges_order[i].second << "("
             << codes[edges_order[i].second] << ")\"";
        if (matching.find(edges_order[i]) != matching.end()) {
            fout << "[color = \"red\"]\n";
        } else {
            fout << "\n";
        }
    }

    fin.close();
    fout.close();

    fin.open("../../vcover.txt");
    fout.open("../../vcovering.txt");

    std::vector<int> vcover(25);
    for (size_t i = 0; i < 25; i++) {
        fin >> vcover[i];
    }
    for (size_t i = 0; i < order.size(); i++) {
        fout << "\"" << order[i] << "(" << codes[order[i]] << ")\"";
        if (std::find(vcover.begin(), vcover.end(), order[i]) != vcover.end()) {
            fout << "[color = \"" << colors[1] << "\"]\n";
        } else {
            fout << "\n";
        }
    }
    fin.close();
    fout.close();

    fin.open("../../center.txt");
    fout.open("../../center colored.txt");
    std::vector<int> center(13);
    for (size_t i = 0; i < 13; i++) {
        fin >> center[i];
    }
    for (size_t i = 0; i < order.size(); i++) {
        fout << "\"" << order[i] << "(" << codes[order[i]] << ")\"";
        if (std::find(center.begin(), center.end(), order[i]) != center.end()) {
            fout << "[color = \"" << colors[1] << "\"]\n";
        } else {
            fout << "\n";
        }
    }

    fin.close();
    fout.close();

    fin.open("../../hamiltonian.txt");
    fout.open("../../hamiltonian graphviz.txt");
    std::set<std::pair<int, int>> ham;  // i'm hungry
    fin >> a;
    for (size_t i = 1; i < 35; i++) {
        fin >> b;
        if (a > b) {
            ham.insert(std::make_pair(b, a));
        } else {
            ham.insert(std::make_pair(a, b));
        }
        a = b;
    }
    for (size_t i = 0; i < 91; i++) {
        fout << "\"" << edges_order[i].first << "("
             << codes[edges_order[i].first] << ")\" -- "
             << "\"" << edges_order[i].second << "("
             << codes[edges_order[i].second] << ")\"";
        if (ham.find(edges_order[i]) != ham.end()) {
            fout << "[color = \"red\"]\n";
        } else {
            fout << "\n";
        }
    }

    fin.close();
    fout.close();

    fin.open("../../ecover.txt");
    fout.open("../../ecovering.txt");
    std::set<std::pair<int, int>> ecover;
    for (size_t i = 0; i < 24; i++) {
        fin >> a >> b;
        ecover.insert(std::make_pair(a, b));
    }
    for (size_t i = 0; i < 91; i++) {
        fout << "\"" << edges_order[i].first << "("
             << codes[edges_order[i].first] << ")\" -- "
             << "\"" << edges_order[i].second << "("
             << codes[edges_order[i].second] << ")\"";
        if (ecover.find(edges_order[i]) != ecover.end()) {
            fout << "[color = \"red\"]\n";
        } else {
            fout << "\n";
        }
    }
    return 0;
}