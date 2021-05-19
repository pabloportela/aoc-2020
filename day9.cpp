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


Number find_solution_for_part2(const Numbers &numbers, const Number target_sum) {
    // fast-slow pointer
    for (size_t i=0; i<numbers.size()-1; i++) {
        // make sure we start with two numbers
        Number min_number = min(numbers.at(i), numbers.at(i+1));
        Number max_number = max(numbers.at(i), numbers.at(i+1));
        Number current_sum = numbers.at(i) + numbers.at(i+1);

        // expand until we either find the target or we go beyond it
        size_t r_idx = i+1;
        while (r_idx<numbers.size()-1 && current_sum < target_sum) {
            r_idx++;
            Number current_number = numbers.at(r_idx);
            current_sum += current_number;
            if (current_number < min_number) min_number = current_number;
            if (current_number > max_number) max_number = current_number;
        }

        // found it
        if (current_sum == target_sum) {
            return min_number + max_number;
        }
    }

    throw runtime_error("Unable to find sequence for part 2.");
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

    // part 2 and sorry did not find a better name
    Number part2 = find_solution_for_part2(numbers, first_non_compliant);
    cout << "Solution for part 2 is " << part2 << ".\n";

    return 0;
}
