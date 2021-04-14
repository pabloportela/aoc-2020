import sys
from typing import List


def distinct_answer_count(group_answers: List[str]) -> int:
    distinct = set(group_answers[0])
    for answers in group_answers[1:]:
        distinct |= set(answers)

    return len(distinct)

def common_answer_count(group_answers: List[str]) -> int:
    common = set(group_answers[0])
    for answers in group_answers[1:]:
        common &= set(answers)

    return len(common)


def main():
    # read whole file into a string
    with open(sys.argv[1], 'r') as f:
        forms = f.read().strip()

    groups_answers: List[List[str]] = [ga_str.split("\n") for ga_str in forms.split("\n\n")]

    # part 1
    distinct_answer_sum = sum(distinct_answer_count(ga) for ga in groups_answers)
    print("distinct answer sum: " + str(distinct_answer_sum))

    # part 2
    common_answer_sum = sum(common_answer_count(ga) for ga in groups_answers)
    print("common answer sum: " + str(common_answer_sum))


main()
