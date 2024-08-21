#!/usr/bin/env python3
import itertools
import sys
import re

with open(sys.argv[1]) as file:
    contents = file.readlines()

def match_instruction(direction):
    return re.match(
        r'(?P<key>\w\w\w) = \((?P<left>\w\w\w), (?P<right>\w\w\w)',
        direction
    )

instructions = list(contents[0].strip())
maps = {
    m.group('key') : {'L' : m.group('left'), 'R' : m.group('right')}
    for m in [ match_instruction(d) for d in contents[2:]] if m is not None
}

key = 'AAA'
for run, instruction in enumerate(itertools.cycle(instructions)):
    if key == 'ZZZ':
        print(run)
        break
    key = maps[key][instruction]
