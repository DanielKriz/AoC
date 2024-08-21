use std::io;
use std::io::prelude::*;

fn main() {
    let (mut distance, mut depth): (i32, i32) = (0, 0);
    for line in io::stdin().lock().lines() {
        let (mut dir, mut val): (String, i32) = ("".to_string(), 0);
        for (i, word) in line.unwrap().split_whitespace().enumerate() {
            if i % 2 == 0 {
                dir = word.to_string();
            } else {
                val = word.parse::<i32>().unwrap();
            }
        }
        match dir.as_str() {
            "forward" => distance += val,
            "down" => depth += val,
            "up" => depth -= val,
            _ => (),
        }
    }
    println!("{}", distance * depth);
}
