#!/usr/bin/env python3
import sys
import collections

with open(sys.argv[1]) as file:
    contents = [line.strip() for line in file.readlines()]

delimeter = contents.index('')

rules = collections.defaultdict(list)
for k, v in [tuple(x.split('|')) for x in contents[:delimeter]]:
    rules[int(k)].append(int(v))
updates = [[int(y) for y in x.split(',')] for x in contents[delimeter+1:]]

correct = []
for update in updates:
    is_correct = True;
    for idx in range(len(update)):
        for page in update[idx:]:
            if not (page == update[idx] or page in rules[update[idx]]):
                is_correct = False
    if is_correct:
        correct.append(update)

print(sum([x[len(x) // 2] for x in correct]))
