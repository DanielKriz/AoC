#!/usr/bin/env python3
import sys

with open(sys.argv[1]) as file:
    contents = file.readlines()

first, second = (list(), list())
for line in contents:
    num1, num2 = line.strip().split('   ')
    first.append(int(num1))
    second.append(int(num2))

mmap = {}
for num in second:
    mmap[num] = 1 if num not in mmap.keys() else mmap[num] + 1

result = 0
for num in first:
    result += num * mmap[num] if num in mmap.keys() else 0

print(result)
