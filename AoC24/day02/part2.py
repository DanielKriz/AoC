#!/usr/bin/env python3
import sys

with open(sys.argv[1]) as file:
    contents = file.readlines()


def is_safe(level_report):
    nums = list(map(lambda x: x[1] - x[0], zip(level_report, level_report[1:])))
    inc_or_dec = all(map(lambda x: x > 0, nums)) or all(map(lambda x: x < 0, nums))
    in_bounds = all(map(lambda x: abs(x) >= 1 and abs(x) <= 3, nums))
    return inc_or_dec and in_bounds


result = 0
for line in contents:
    nums = list(map(int, line.strip().split(' ')))
    if is_safe(nums):
        result += 1
    else:
        for idx in range(len(nums)):
            nums_copy = nums.copy()
            nums_copy.pop(idx)
            if is_safe(nums_copy):
                result += 1
                break

print(result)
