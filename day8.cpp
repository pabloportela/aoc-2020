#include <fstream>
#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#include <stdexcept>


using namespace std;


struct Instruction
{
    string op;
    int arg;

    Instruction(string op, const int arg) : op(std::move(op)), arg(arg) {}
};


using Instructions = vector<Instruction>;


Instructions parse_instructions(const char *filename)
{
    /*
     * Instruction: op + argument
     * Assumes first three chars are op, then an argument integer
    */

    Instructions instructions{};

    fstream file;
    file.open(filename);
    assert(file.is_open());

    string line;
    while (getline(file, line)) {
        instructions.emplace_back(
            line.substr(0, 3),
            stoi(line.substr(4))
        );
    }

    return instructions;
}


class InfiniteLoop : public runtime_error
{
    public:
    InfiniteLoop(const string &msg) noexcept : runtime_error(msg) {}
};


int execute_instructions(const Instructions &instructions) {
    /*
     * ad-hoc executor, bound for refactoring should this get more complex
     */

    int ip = 0;
    int acc = 0;
    vector<bool> executed_positions(instructions.size(), false);

    while (ip < static_cast<int>(instructions.size())) {
        assert(ip >= 0);

        // loop found, stop
        if (executed_positions.at(ip) == true)
            throw InfiniteLoop("Stopping right before executing position " + to_string(ip) + " again. Accumulator value is " + to_string(acc) + ".");

        executed_positions[ip] = true;

        auto ins = instructions.at(ip);
        if (ins.op == "acc") {
            acc += ins.arg;
            ip++;
        }
        else if (ins.op == "jmp") {
            ip += ins.arg;
        }
        else if (ins.op ==  "nop") {
            ip++;
        }
        else {
            throw runtime_error("Invalid operation: " + ins.op);
        }
    }

    return acc;
}

void fix_instructions(Instructions &instructions) {
    /*
     * Assumes instructions are broken because of a swapped `jmp` , `nop` (or the other way round)
     * Tries every swapping combination to fix them.
     */

    for (size_t i=0; i<instructions.size(); i++) {

        if (instructions.at(i).op == "acc")
            continue;

        // temporarily swap an operation
        string swapped_op;
        if (instructions.at(i).op == "jmp") {
            swapped_op = "jmp";
            instructions[i].op = "nop";
        }
        else {
            assert(instructions.at(i).op == "nop");
            swapped_op = "nop";
            instructions[i].op = "jmp";
        }

        // try this combination
        try {
            execute_instructions(instructions);
            // instructions are fixed now
            return;
        }
        catch (const InfiniteLoop &e) {
            // did not work, restore instruction
            instructions[i].op = swapped_op;
        }
    }

    throw runtime_error("Unable to fix instructions.");
}


int main(int argc, char **argv)
{
    Instructions instructions = parse_instructions(argv[1]);

    // part 1
    try {
        execute_instructions(instructions);
    }
    catch (const InfiniteLoop &e) {
        cout << e.what() << endl;
    }

    // part 2
    fix_instructions(instructions);
    auto acc_value_after_fix = execute_instructions(instructions);
    cout << "Fixed instructions and executed them until completion. Accumulator value is " << acc_value_after_fix << ".\n";
}
