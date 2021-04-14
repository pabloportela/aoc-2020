import sys


def seat_code_to_id(seat: str) -> int:
    assert len(seat) == 10
    return int("0b" + seat[:7].replace('F', '0').replace('B', '1') + seat[7:].replace('L', '0').replace('R', '1'), 2)


def main():
    assert len(sys.argv) == 2

    # read file
    with open(sys.argv[1], 'r') as f:
        lines = f.readlines()

    # test
    assert seat_code_to_id("FBFBBFFRLR") == 357
    assert seat_code_to_id("BFFFBBFRRR") == 567
    assert seat_code_to_id("FFFBBBFRRR") == 119
    assert seat_code_to_id("BBFFBBFRLL") == 820

    # parse seats into offsets
    seats = [False] * 1024
    max_seat_id = -1
    for l in lines:
        seat_id = seat_code_to_id(l.strip())
        seats[seat_id] = True
        if seat_id > max_seat_id:
            max_seat_id = seat_id


    # part 1
    assert max_seat_id != -1
    print(max_seat_id)

    # part 2
    seat_id = 0
    while seats[seat_id] is False:
        seat_id += 1
    while seats[seat_id] is True:
        seat_id += 1

    print(seat_id)


main()
