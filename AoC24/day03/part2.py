#!/usr/bin/env python3
import sys
import re

with open(sys.argv[1]) as file:
    contents = file.readlines()

pattern = r'mul\((?P<lhs>\d+),(?P<rhs>\d+)\)|(do\(\))|(don\'t\(\))'
multiples = sum([re.findall(pattern, x) for x in contents], [])

result = 0
is_enabled = True
for x, y, start, stop in multiples:
    match (start, stop):
        case ('do()', _):
            is_enabled = True
        case (_, 'don\'t()'):
            is_enabled = False
        case ('', ''):
            result += int(x) * int(y) if is_enabled else 0

print(result)
