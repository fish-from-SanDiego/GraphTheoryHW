#include <algorithm>
#include <fstream>
#include <limits>
#include <set>
#include <string>
#include <vector>

struct Node {
    int label;
    int weight;  // weight of the edge from some other vertex to this one
    Node(int l, int w) : label(l), weight(w){};
    bool operator==(const Node& other) const {
        return other.label == label && other.weight == weight;
    };
};

template <typename T>
class MinQueue {
   private:
    std::vector<std::pair<T, int>> heap;

   public:
    void push(const T& val, int priority) {
        heap.push_back(std::make_pair(val, priority));
        int i = heap.size() - 1;
        while (i > 0 && heap[(i - 1) / 2].second > heap[i].second) {
            swap(heap[(i - 1) / 2], heap[i]);
            i = (i - 1) / 2;
        }
    }

    void decreaseKey(const T& val, int priority) {
        int i;
        for (i = 0; i < heap.size(); i++) {
            if (heap[i].first == val) {
                heap[i].second = priority;
                break;
            }
        }
        while (i > 0 && heap[(i - 1) / 2].second > heap[i].second) {
            swap(heap[(i - 1) / 2], heap[i]);
            i = (i - 1) / 2;
        }
    }

    T extractMin() {
        T min_elem = heap[0].first;
        heap[0] = heap.back();
        heap.pop_back();
        int i = 0;
        while (2 * i + 1 < heap.size()) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int min = left;
            if (right < heap.size() && heap[right].second < heap[left].second) {
                min = right;
            }
            if (heap[i].second > heap[min].second) {
                swap(heap[i], heap[min]);
                i = min;
            } else {
                break;
            }
        }
        return min_elem;
    }

    bool empty() { return heap.empty(); }
};

std::vector<std::pair<int, Node>> Prim(
    const std::vector<std::vector<Node>>& adjl) {
    std::vector<std::pair<int, Node>> edges;
    MinQueue<int> q;
    std::vector<int> p(adjl.size());
    std::vector<bool> in_tree(adjl.size(), false);
    std::vector<int> key(adjl.size(), std::numeric_limits<int>::max());
    std::vector<std::vector<int>> weight(
        adjl.size(),
        std::vector<int>(adjl.size(), std::numeric_limits<int>::max()));
    for (size_t i = 1; i < adjl.size(); i++) {
        q.push(i, std::numeric_limits<int>::max());
        for (size_t j = 0; j < adjl[i].size(); j++) {
            weight[i][adjl[i][j].label] = adjl[i][j].weight;
        }
    }
    key[1] = 0;
    q.decreaseKey(1, key[1]);
    while (!q.empty()) {
        int v = q.extractMin();
        in_tree[v] = true;
        for (size_t u = 1; u < adjl.size(); u++) {
            if (weight[v][u] == std::numeric_limits<int>::max() || in_tree[u] ||
                key[u] <= weight[v][u]) {
                continue;
            }
            p[u] = v;
            key[u] = weight[v][u];
            q.decreaseKey(u, key[u]);
        }
        if (v != 1) {
            if (v < p[v]) {
                edges.push_back(std::make_pair(v, Node(p[v], weight[v][p[v]])));
            } else {
                edges.push_back(std::make_pair(p[v], Node(v, weight[v][p[v]])));
            }
        }
    }
    return edges;
}

void dfs(const std::vector<std::vector<int>>& tree_matrix, int v, int p,
         std::vector<bool>& used, int& weight) {
    used[v] = true;
    for (int u = 0; u < tree_matrix[v].size(); u++) {
        if (u == p || used[u] ||
            tree_matrix[v][u] == std::numeric_limits<int>::max())
            continue;
        weight += tree_matrix[v][u];
        dfs(tree_matrix, u, v, used, weight);
    }
}

std::set<int> centroid(const std::vector<std::vector<int>>& tree_matrix) {
    std::vector<int> weights(tree_matrix.size());
    for (size_t i = 0; i < tree_matrix.size(); i++) {
        std::vector<int> branch_weights;
        for (size_t j = 0; j < tree_matrix[i].size(); j++) {
            if (tree_matrix[i][j] == std::numeric_limits<int>::max()) {
                continue;
            }
            int weight = tree_matrix[i][j];
            std::vector<bool> used(tree_matrix.size(), false);
            used[i] = true;
            dfs(tree_matrix, j, i, used, weight);
            branch_weights.push_back(weight);
        }
        weights[i] =
            *std::max_element(branch_weights.begin(), branch_weights.end());
    }
    int min_w = *std::min_element(weights.begin(), weights.end());
    std::set<int> ctd;
    for (size_t i = 0; i < tree_matrix.size(); i++) {
        if (weights[i] == min_w) {
            ctd.insert(i + 1);
        }
    }
    return ctd;
}

int main(int, char**) {
    std::vector<std::string> codes = {
        "",   "AL", "AD", "AM", "AT", "BY", "BE", "BA", "BG", "HR", "CZ", "DK",
        "EE", "FI", "FR", "GE", "DE", "GR", "HU", "IT", "XK", "LV", "LI", "LT",
        "LU", "MD", "MC", "ME", "NL", "MK", "NO", "PL", "PT", "RO", "RU", "SM",
        "RS", "SK", "SI", "ES", "SE", "CH", "TR", "UA", "VA"};
    std::vector<std::vector<Node>> adjl(45);
    std::ifstream fin("../../edges weighted.txt");
    std::vector<std::pair<int, Node>> edges_order;
    std::vector<int> order;
    int a, b, c;
    for (size_t i = 0; i < 91; i++) {
        fin >> a >> b >> c;
        adjl[a].push_back(Node(b, c));
        adjl[b].push_back(Node(a, c));
        edges_order.push_back(std::make_pair(a, Node(b, c)));
        if (std::find(order.begin(), order.end(), a) == order.end()) {
            order.push_back(a);
        }
        if (std::find(order.begin(), order.end(), b) == order.end()) {
            order.push_back(b);
        }
    }
    auto MST = Prim(adjl);
    std::ofstream fout("../../tree edges.txt");
    for (size_t i = 0; i < MST.size(); i++) {
        fout << MST[i].first << ' ' << MST[i].second.label << ' '
             << MST[i].second.weight << '\n';
    }
    fout.close();
    fout.open("../../tree edges graphviz.txt");
    for (size_t i = 0; i < edges_order.size(); i++) {
        auto t = edges_order[i];
        auto edge = std::find(MST.begin(), MST.end(), t);
        if (edge != MST.end()) {
            fout << "\"" << edge->first << "(" << codes[edge->first]
                 << ")\" -- \"" << edge->second.label << "("
                 << codes[edge->second.label]
                 << ")\"[label = " << edge->second.weight << "]\n";
        }
    }
    std::vector<std::vector<int>> adjm(
        44, std::vector<int>(44, std::numeric_limits<int>::max()));
    for (size_t i = 0; i < MST.size(); i++) {
        adjm[MST[i].first - 1][MST[i].second.label - 1] =
            adjm[MST[i].second.label - 1][MST[i].first - 1] =
                MST[i].second.weight;
    }
    fout.close();
    fout.open("../../centroid vertices.txt");
    auto ctd = centroid(adjm);
    for (auto i = ctd.begin(); i != ctd.end(); ++i) {
        fout << *i << ' ';
    }
    fout.close();
    fout.open("../../prufer.txt");
    std::string prufer = "";
    std::vector<std::vector<int>> adjMST(adjm.size() + 1);
    for (size_t i = 0; i < MST.size(); i++) {
        int v = MST[i].first;
        int u = MST[i].second.label;
        adjMST[v].push_back(u);
        adjMST[u].push_back(v);
    }
    for (size_t i = 1; i <= adjMST.size() - 3; i++) {
        for (size_t j = 1; j < adjMST.size(); j++) {
            if (adjMST[j].size() != 1) {
                continue;
            }
            prufer += std::to_string(adjMST[j][0]) + ".";  // . is the delimeter
            adjMST[adjMST[j][0]].erase(std::find(
                adjMST[adjMST[j][0]].begin(), adjMST[adjMST[j][0]].end(), j));
            adjMST[j].clear();
            break;
        }
    }
    prufer.pop_back();  // one extra '.' is redundant
    fout << prufer;
    return 0;
}
