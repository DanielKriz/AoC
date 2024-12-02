#!/usr/bin/env python3
import sys

with open(sys.argv[1]) as file:
    contents = file.readlines()

first, second = (list(), list())
for line in contents:
    num1, num2 = line.strip().split('   ')
    first.append(num1)
    second.append(num2)

first.sort()
second.sort()

result = 0
for num1, num2 in zip(first, second):
    result += abs(int(num1) - int(num2))

print(result)
