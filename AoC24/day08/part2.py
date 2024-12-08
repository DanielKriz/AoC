#!/usr/bin/env python3
import sys
import collections

class Vector:
    def __init__(self, x, y):
        self.data = [x, y]

    def __eq__(self, other):
        if isinstance(other, tuple):
            return self.x == other[0] and self.y == other[1]
        else:
            return self.data == other

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

    def __mul__(self, other):
        return Vector(self.x * other.x, self.y * other.y)

    def __sub__(self, other):
        return Vector(self.x - other.x, self.y - other.y)

    def __div__(self, other):
        return Vector(self.x / other.x, self.y / other.y)

    def __abs__(self):
        return Vector(abs(self.x), abs(self.y))

    def __neg__(self):
        return Vector(-self.x, -self.y)

    def __repr__(self):
        return f'({self.x}, {self.y})'

    def __hash__(self):
        return hash(tuple(self.data))

    def difference(self, other):
        return abs(self - other)

    @property
    def x(self):
        return self.data[0]

    @property
    def y(self):
        return self.data[1]

with open(sys.argv[1]) as file:
    contents = [list(line.strip()) for line in file.readlines()]


map = {}
antennas = collections.defaultdict(list)
for idx in range(len(contents)):
    for jdx in range(len(contents[0])):
        map[Vector(idx, jdx)] = contents[idx][jdx]
        if contents[idx][jdx] != '.':
            antennas[contents[idx][jdx]].append(Vector(idx, jdx))

antinodes = set()

for antenna in antennas.keys():
    for location in antennas[antenna]:
        for other in antennas[antenna]:
            diff = location - other
            if diff == (0, 0):
                antinodes.add(location)
                continue
            diff = -diff
            new_pos = location - diff
            if new_pos.x < 0 or new_pos.y < 0:
                continue
            while True:
                try:
                    contents[new_pos.x][new_pos.y] = '#' if contents[new_pos.x][new_pos.y] == '.' else contents[new_pos.x][new_pos.y]
                    antinodes.add(new_pos)
                    new_pos -= diff
                    if new_pos.x < 0 or new_pos.y < 0:
                        break
                except Exception as err:
                    break

print(len(antinodes))
