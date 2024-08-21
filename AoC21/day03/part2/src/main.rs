use std::io;
use std::io::prelude::*;

const BINARY_LEN: usize = 12;

fn main() {
    let mut nums: Vec<u32> = Vec::new();

    for line in io::stdin().lock().lines() {
        nums.push(u32::from_str_radix(line.unwrap().as_str(), 2).unwrap());
    }

    let mut nums2: Vec<u32> = nums.to_vec();
    for i in 0..BINARY_LEN {
        let ones: Vec<u32> = nums
            .iter()
            .cloned()
            .filter(|x| ((*x & (1 << i)) > 0))
            .collect();

        let zeros: Vec<u32> = nums
            .iter()
            .cloned()
            .filter(|x| ((*x & (1 << i)) == 0))
            .collect();

        println!("{} >= {}", ones.iter().count(), zeros.iter().count());
        if ones.iter().count() >= zeros.iter().count() {
            nums = ones.to_vec();
        } else {
            nums = zeros.to_vec();
        }

        if nums2.iter().count() == 1 {
            continue;
        }

        let ones: Vec<u32> = nums2
            .iter()
            .cloned()
            .filter(|x| ((*x & (1 << i)) > 0))
            .collect();

        let zeros: Vec<u32> = nums2
            .iter()
            .cloned()
            .filter(|x| ((*x & (1 << i)) == 0))
            .collect();

        println!("{} <= {}", ones.iter().count(), zeros.iter().count());
        if zeros.iter().count() <= ones.iter().count() {
            nums2 = zeros.to_vec();
        } else {
            nums2 = ones.to_vec();
        }
    }
    // println!("{:#0b}", num);
    println!("{}", nums[0]);
    println!("{}", nums2[0]);
    println!("{}", nums[0] * nums2[0]);
}
