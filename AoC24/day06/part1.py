#!/usr/bin/env python3
import sys

def add_tuples(lhs, rhs):
    return tuple([sum(x) for x in zip(lhs, rhs)])

with open(sys.argv[1]) as file:
    contents = [line.strip() for line in file.readlines()]


map = dict()
position = tuple()
for idx in range(len(contents)):
    for jdx in range(len(contents[0])):
        symbol = contents[idx][jdx]
        if symbol == '^':
            position = (idx, jdx)
        map[(idx, jdx)] = contents[idx][jdx]

directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
direction_idx = 0
result = 0
prev_position = position
while True:
    try:
        if map[position] != '#':

            result += 1 if map[position] != 'X' else 0
            map[position] = 'X'
            prev_position = position
            position = add_tuples(directions[direction_idx], position)
        else:
            position = prev_position
            direction_idx = (direction_idx + 1) % len(directions)
    except KeyError as err:
        print(result)
        break
