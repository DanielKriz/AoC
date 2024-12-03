#!/usr/bin/env python3
import sys
import re

with open(sys.argv[1]) as file:
    contents = file.readlines()

pattern = r'mul\((?P<lhs>\d+),(?P<rhs>\d+)\)'
multiples = sum([re.findall(pattern, x) for x in contents], [])
result = sum([int(x) * int(y) for x, y in multiples])
print(result)
