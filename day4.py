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

    def add_field(self, key, value):
        self.fields[key] = value

    def is_valid_passport(self) -> bool:
        return all(key in self.fields for key in self.required_keys)


def parse_document(chunk: str) -> Document:
    document = Document()
    # split by whitespace into key:value
    for field in chunk.split():
        document.add_field(*field.split(":"))

    return document


def parse_documents(content: str) -> List[Document]:
    # read whole file into a string
    with open(sys.argv[1], 'r') as f:
        content = f.read()

    # split each record and add them to a list
    return map(parse_document, content.split("\n\n"))


def main():
    assert len(sys.argv) == 2

    documents = parse_documents(sys.argv[1])
    q_valid_passports = sum(d.is_valid_passport() for d in documents)

    print(q_valid_passports)


main()
