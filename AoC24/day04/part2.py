#!/usr/bin/env python3
import sys
import regex as re

with open(sys.argv[1]) as file:
    contents = [line.strip() for line in file.readlines()]

result = 0

grid = dict()

for x in range(-3, len(contents[0]) + 3):
    grid[(-1, x)] = '0'
    grid[(-2, x)] = '0'
    grid[(-3, x)] = '0'
    grid[(len(contents) + 0, x)] = '0'
    grid[(len(contents) + 1, x)] = '0'
    grid[(len(contents) + 2, x)] = '0'
    grid[(len(contents) + 3, x)] = '0'

for idx in range(len(contents)):
    grid[(idx, -1)] = '0'
    grid[(idx, -2)] = '0'
    grid[(idx, -3)] = '0'
    grid[(idx, len(contents[0]) + 0)] = '0'
    grid[(idx, len(contents[0]) + 1)] = '0'
    grid[(idx, len(contents[0]) + 2)] = '0'
    grid[(idx, len(contents[0]) + 3)] = '0'
    for jdx in range(len(contents[0])):
        grid[(idx, jdx)] = contents[idx][jdx]

for x in range(len(contents)):
    for y in range(len(contents)):
        if grid[(x, y)] == 'A':
            count = 0
            if grid[(x-1, y-1)] + 'A' + grid[(x+1, y+1)] == 'MAS':
                count += 1
            if grid[(x+1, y+1)] + 'A' + grid[(x-1, y-1)] == 'MAS':
                count += 1
            if grid[(x-1, y+1)] + 'A' + grid[(x+1, y-1)] == 'MAS':
                count += 1
            if grid[(x+1, y-1)] + 'A' + grid[(x-1, y+1)] == 'MAS':
                count += 1
            if (count == 2):
                result += 1

print(result)