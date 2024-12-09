#!/usr/bin/env python3
import sys
import itertools
import operator

with open(sys.argv[1]) as file:
    contents = [line.strip() for line in file.readlines()]

# add padding so that we can use batched iterator
contents[0] += '0'

idx_dispatcher = itertools.count()
id_dispatcher = itertools.count()

memory_array = []
empty_cells = []

for (file_size, padding_size) in itertools.batched(contents[0], 2):
    id = next(id_dispatcher)
    for memory in range(int(file_size)):
        next(idx_dispatcher)
        memory_array.append(id)
    for empty in range(int(padding_size)):
        memory_array.append(-1)
        next_idx = next(idx_dispatcher)
        empty_cells.append(next_idx)

packed_memory = []
reversed_memory = reversed(memory_array)
for idx in range(len(memory_array) - len(empty_cells)):
    if len(empty_cells) != 0 and idx == empty_cells[0]:
        empty_cells.pop(0)
        new_value = next(reversed_memory)
        while new_value == -1:
            new_value = next(reversed_memory)
        packed_memory.append((idx, new_value))
    else:
        packed_memory.append((idx, memory_array[idx]))

print(sum(itertools.starmap(operator.mul, packed_memory)))
