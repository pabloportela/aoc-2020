from __future__ import annotations

import re
import sys
from typing import List


class Document:

    required_keys = {
        "byr", #  (Birth Year)
        "iyr", #  (Issue Year)
        "eyr", #  (Expiration Year)
        "hgt", #  (Height)
        "hcl", #  (Hair Color)
        "ecl", #  (Eye Color)
        "pid", #  (Passport ID)
        # "cid", #  (Country ID)
    }

    def __init__(self):
        self.fields = dict()

    @staticmethod
    def parse_document(chunk: str) -> Document:
        document = Document()
        # split by whitespace into key:value
        for field in chunk.split():
            document.add_field(*field.split(":"))

        return document

    @classmethod
    def parse_from_file(cls, content: str) -> List[Document]:
        # read whole file into a string
        with open(sys.argv[1], 'r') as f:
            content = f.read()

        # split each record and add them to a list
        return list(map(cls.parse_document, content.split("\n\n")))

    def add_field(self, key, value):
        self.fields[key] = value

    def is_passport_really_valid(self) -> bool:
        # previous validation still applies
        if not self.is_passport_valid():
            return False

        # byr (Birth Year)
        if not self._is_year_valid(self.fields["byr"], 1920, 2002):
            return False

        # iyr (Issue Year)
        if not self._is_year_valid(self.fields["iyr"], 2010, 2020):
            return False

        # eyr (Expiration Year)
        if not self._is_year_valid(self.fields["eyr"], 2020, 2030):
            return False

        # hgt (Height) - a number followed by either cm or in:
        if not self._is_height_valid(self.fields["hgt"]):
            return False

        # hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
        if not self._is_hair_color_valid(self.fields["hcl"]):
            return False

        # ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
        if not self._is_eye_color_valid(self.fields["ecl"]):
            return False

        # pid (Passport ID) - a nine-digit number, including leading zeroes.
        if not self._is_passport_id_valid(self.fields["pid"]):
            return False

        return True

    @staticmethod
    def _is_passport_id_valid(passport_id: str):
        return re.search("^\d{9}$", passport_id)

    @staticmethod
    def _is_eye_color_valid(eye_color: str) -> bool:
        return eye_color in ("amb", "blu", "brn", "gry", "grn", "hzl", "oth")

    @staticmethod
    def _is_hair_color_valid(hair_color: str):
        if not (len(hair_color) == 7 and hair_color[0] == '#'):
            return False

        try:
            int("0x" + hair_color[1:], 16)
            return True
        except ValueError:
            return False

    @staticmethod
    def _is_height_valid(height: str) -> bool:
        if not 4 <= len(height) <= 5:
            return False

        value = int(height[:-2])
        unit = height[-2:]

        if unit == "cm":
            return 150 <= value <= 193

        if unit == "in":
            return 59 <= value <= 76

        raise ValueError

    @staticmethod
    def _is_year_valid(year: str, lower_bound: int, upper_bound: int) -> bool:
        return re.search("^\d{4}$", year) is not None and (lower_bound <= int(year) <= upper_bound)

    def is_passport_valid(self) -> bool:
        return all(key in self.fields for key in self.required_keys)


def main():
    assert len(sys.argv) == 2
    documents = Document.parse_from_file(sys.argv[1])

    # part 1
    q_valid_passports = sum(d.is_passport_valid() for d in documents)
    print(q_valid_passports)

    # part 2
    q_valid_passports = sum(d.is_passport_really_valid() for d in documents)
    print(q_valid_passports)


main()
