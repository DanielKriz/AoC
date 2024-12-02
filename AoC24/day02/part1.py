#!/usr/bin/env python3
import sys

with open(sys.argv[1]) as file:
    contents = file.readlines()

result = 0
for line in contents:
    nums = list(map(int, line.strip().split(' ')))
    nums = list(map(lambda x: x[1] - x[0], zip(nums, nums[1:])))
    inc_or_dec = all(map(lambda x: x > 0, nums)) or all(map(lambda x: x < 0, nums))
    in_bounds = all(map(lambda x: abs(x) >= 1 and abs(x) <= 3, nums))
    result += 1 if inc_or_dec and in_bounds else 0

print(result)
