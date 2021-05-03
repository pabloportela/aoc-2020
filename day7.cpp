#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <boost/algorithm/string.hpp>

using namespace std;

using ColorQty = pair<int, string>;
using ColorCode = size_t;


vector<vector<ColorQty>> parse_input(const string &filename)
{
    vector<vector<ColorQty>> parsed_input{};

    fstream file;
    file.open(filename);
    assert(file.is_open());

    string line;
    while (getline(file, line)) {
        if (line.find("contain no other bags") != string::npos)
            continue;

        vector<ColorQty> color_quantities{};
        size_t offset;

        // parse container color
        offset = line.find(' ');
        offset = line.find(' ', offset+1);
        color_quantities.emplace_back(1, line.substr(0, offset));

        // parse contained colors
        offset = line.find("contain");
        assert(offset != string::npos);
        string contained_colors = line.substr(offset + 7);
        vector<string> color_qty_str_vec;
        boost::split(color_qty_str_vec, contained_colors, [](char c){return c == ',';});
        for (auto &color_qty_str: color_qty_str_vec) {
            vector<string> color_str_vec;
            boost::split(color_str_vec, color_qty_str, [](char c){return c == ' ';});
            color_quantities.emplace_back(
                stoi(color_str_vec.at(1)),
                color_str_vec.at(2) + ' ' + color_str_vec.at(3)
            );
        }
        parsed_input.push_back(color_quantities);
    }
    file.close();

    return parsed_input;
}


unordered_map<string, ColorCode> map_color_names_to_codes(vector<vector<ColorQty>> &bag_hierarchies) {
    unordered_map<string, ColorCode> color_codes{};
    ColorCode next_color_code = 0;
    for (const auto &color_quantities: bag_hierarchies) {
        for (const auto &color_qty: color_quantities) {
            if (color_codes.count(color_qty.second) == 0) {
                color_codes[color_qty.second] = next_color_code;
                next_color_code++;
            }
        }
    }

    return color_codes;
}


int count_distinct_descendants(unordered_map<ColorCode, unordered_set<ColorCode>> graph, ColorCode start) {
    // BFS to see who can directly or indirectly contain a shiny gold bag
    unordered_set<ColorCode> visited{};
    unordered_set<ColorCode> distinct_descendants{};
    queue<ColorCode> to_visit{};
    to_visit.push(start);
    while (!to_visit.empty()) {
        ColorCode node = to_visit.front();
        if (graph.count(node)) {
            for (const auto &child: graph.at(node)) {
                if (visited.count(child) == 0)
                    to_visit.push(child);
                distinct_descendants.insert(child);
            }
        }

        to_visit.pop();
        visited.insert(node);
    }

    return distinct_descendants.size();
}


int tree_size(unordered_map<ColorCode, unordered_map<ColorCode, int>> graph, ColorCode start) {
    if (!graph.count(start))
        return 1;

    int total = 1;
    for (const auto &[color, qty]: graph.at(start))
        total += qty * tree_size(graph, color);

    return total;
}


int main(int argc, char **argv)
{
    // parse input file
    auto bag_hierarchies = parse_input(argv[1]);

    // map color names to codes
    auto color_codes = map_color_names_to_codes(bag_hierarchies);

    // Part I
    // create a 'contained by' graph via an adjacency list
    unordered_map<ColorCode, unordered_set<ColorCode>> contained_by{};
    for (const auto &color_quantities: bag_hierarchies) {
        ColorCode container = color_codes.at(color_quantities.at(0).second);
        for (size_t i=1; i<color_quantities.size(); i++) {
            ColorCode contained = color_codes.at(color_quantities.at(i).second);
            contained_by[contained].insert(container);
        }
    }

    auto dd = count_distinct_descendants(contained_by, color_codes.at("shiny gold"));
    cout << "Shiny gold bag can be contained by " << dd << " distinct bags\n";

    // Part II
    // create a 'contains' graph via an adjacency list
    unordered_map<ColorCode, unordered_map<ColorCode, int>> contains{};
    for (const auto &color_quantities: bag_hierarchies) {
        ColorCode container = color_codes.at(color_quantities.at(0).second);
        for (size_t i=1; i<color_quantities.size(); i++) {
            ColorCode contained = color_codes.at(color_quantities.at(i).second);
            contains[container][contained] = color_quantities.at(i).first;
        }
    }

    auto tc = tree_size(contains, color_codes.at("shiny gold")) - 1;
    cout << "A shiny gold bag contains " << tc << " bags\n";
}
