use std::io;
use std::io::prelude::*;

const BINARY_LEN: usize = 12;
const BITS32: usize = 32;

fn main() {
    let mut ones_cnt: [u32; BINARY_LEN as usize] = [0; 12];
    let mut num_cnt: u32 = 0;
    for (i, line) in io::stdin().lock().lines().enumerate() {
        let num = u32::from_str_radix(line.unwrap().as_str(), 2).unwrap();
        for j in 0..BINARY_LEN {
            ones_cnt[j] += (num & (1 << j)) >> j;
        }
        num_cnt = i as u32;
    }

    let mut gamma: u32 = 0;
    for i in 0..BINARY_LEN {
        gamma += ((ones_cnt[i] > ((num_cnt + 1) / 2)) as u32) << (i);
    }

    let epsilon: u32 = (!gamma << BITS32 - BINARY_LEN) >> BITS32 - BINARY_LEN;
    println!("{}", gamma as u64 * epsilon as u64);
}
