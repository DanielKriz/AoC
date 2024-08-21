use std::io::stdin;
use std::cmp::*;

fn main() {
    let mut buffer = String::new();
    stdin().read_line(&mut buffer).expect("could not read the line");

    let positions: Vec<u32> = buffer
        .split(",")
        .map(|x| x.trim())
        .filter(|x| !x.is_empty())
        .map(|x| x.parse().unwrap())
        .collect();

    let mut fuels: Vec<u32> = Vec::new();
    for i in 0..=(*positions.iter().max().unwrap()) {
        let mut total_fuel: u32 = 0;
        for position in positions.iter() {
            for j in 1..=(max(*position, i) - min(*position, i)) {
                total_fuel += j;
            }
        }
        fuels.push(total_fuel);
    }
    println!("{}", fuels.iter().min().unwrap());
}
