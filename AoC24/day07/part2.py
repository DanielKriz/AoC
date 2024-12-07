#!/usr/bin/env python3
import sys
import itertools

with open(sys.argv[1]) as file:
    contents = [line.strip() for line in file.readlines()]

add = lambda x: x[0] + x[1]
mul = lambda x: x[0] * x[1]
con = lambda x: int(str(x[0]) + str(x[1]))

calibrations = [int(x.split(':')[0]) for x in contents]
equations = [list(map(int, x.split(':')[1].strip().split(' '))) for x in contents]

total = 0
for desired_result, values in zip(calibrations, equations):
    for operator_permutation in itertools.product([add, mul, con], repeat=len(values) - 1):
        values_iter = iter(values)
        result = next(values_iter)
        for operator in operator_permutation:
            result = operator((result, next(values_iter)))
        if result == desired_result:
            total += result
            break
print(total)
