#!/usr/bin/env python3
import sys
import itertools
import operator

with open(sys.argv[1]) as file:
    contents = [line.strip() for line in file.readlines()]

# add padding so that we can use batched iterator
contents[0] += '0'

id_dispatcher = itertools.count()
memory = []

for idx, (file_size, padding_size) in enumerate(itertools.batched(contents[0], 2)):
    id = next(id_dispatcher)
    memory.append((id, int(file_size)))
    padding_size = int(padding_size)
    if padding_size != 0:
        memory.append((-1, padding_size))

memory_cpy = memory.copy()
for jdx, memory_block in enumerate(reversed(memory_cpy), start=1):
    if memory_block[0] == -1:
        continue
    for idx, mem in enumerate(memory):
        if mem == memory_block:
            break
        if mem[0] == -1 and mem[1] >= memory_block[1]:
            empty_mem = memory.pop(idx)
            if empty_mem[1] != memory_block[1]:
                memory.insert(idx, (-1, empty_mem[1] - memory_block[1]))
                if memory[idx - 1][0] == -1:
                    memory[idx] = (-1, memory[idx][1] + memory[idx - 1][1])
                    del memory[idx - 1]
                if memory[idx + 1][0] == -1:
                    memory[idx] = (-1, memory[idx][1] + memory[idx + 1][1])
                    del memory[idx + 1]
            memory.insert(idx, memory_block)
            old_idx = -(list(reversed(memory)).index(memory_block) + 1)
            memory[old_idx] = (-1, memory_block[1])
            if jdx == 1:
                break
            if memory[old_idx - 1][0] == -1:
                memory[old_idx] = (-1, memory[old_idx][1] + memory[old_idx - 1][1])
                del memory[old_idx - 1]
            if memory[old_idx + 1][0] == -1:
                memory[old_idx] = (-1, memory[old_idx][1] + memory[old_idx + 1][1])
                del memory[old_idx + 1]
            break

idx_dispatcher = itertools.count()
packed_memory = []
for id, size in memory:
    for _ in range(size):
        packed_memory.append((next(idx_dispatcher), id if id != -1 else 0))

print(sum(itertools.starmap(operator.mul, packed_memory)))
