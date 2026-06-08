mod matrix;

use matrix::Matrix;

fn main() {
    let m1 = Matrix::<i32>::new(1, 3);
    println!("{}", m1);
    let mut m2 = Matrix::from_vec(1, 3, vec![1, 2, 3]);
    m2 = m2 + m1.clone();
    let m3 = Matrix::from_vec(3, 1, vec![3, 2, 1]);
    let m4 = m2.clone() * m3.clone();
    println!("{}", m1);
    let mut m5 = m4 * 2;
    m5 *= 2;
    println!("{}", m2);
    println!("{}", m3);
    println!("{}", m5);
}
