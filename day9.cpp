#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <set>


using namespace std;
using Number = int64_t;
using Numbers = vector<Number>;


Numbers parse_input(const char *filename) {
    // open file
    fstream file;
    file.open(filename);
    assert(file.is_open());

    // parse long integers into a vector
    string tp;
    Numbers integers;
    while (getline(file, tp)) {
        integers.push_back(stoll(tp));
    }
    file.close();

    return integers;
}


bool is_sum_of_two(const Number n, const set<Number> &last_25) {
    for (const auto c: last_25) {
        if (last_25.count(n-c))
            return true;
    }

    return false;
}


Number find_first_non_compliant(const Numbers &numbers, const int preamble_size) {

    // sliding window
    set<Number> last_25(numbers.begin(), numbers.begin() + preamble_size);

    // find the first element one which does not comply
    for (size_t i=preamble_size; i<numbers.size(); i++) {
        // check compliance
        if (!is_sum_of_two(numbers.at(i), last_25)) {
            return numbers.at(i);
        }

        // update last_25
        last_25.erase(numbers.at(i-preamble_size));
        last_25.insert(numbers.at(i));
    }

    throw runtime_error("Unable to find such number.");
}


int main(int argc, char **argv) {
    // gather params
    auto filename = argv[1];
    auto preamble_size = stoi(string(argv[2]));

    // parse input file
    Numbers numbers = parse_input(filename);

    // part 1
    Number first_non_compliant = find_first_non_compliant(numbers, preamble_size);
    cout << "The first number which does not have such property is " << first_non_compliant << ".\n";

    return 0;
}
