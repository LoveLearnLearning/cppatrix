use std::ops::{Add, AddAssign, Mul};

use crate::matrix::Matrix;

pub fn forward<T: Default + Clone + Add<Output = T> + AddAssign + Mul<Output = T>>(
    params: &Matrix<T>,
    weight: &Matrix<T>,
    bais: &Matrix<T>,
) -> Matrix<T> {
    weight.clone() * params.clone() + bais.clone()
}

pub fn mean_square_equation<T: Default + Clone>(train: &Matrix<T>, w: T) {
    let mut diff: f32 = 0.0;
    let mut cost: f32 = 0.0;

    for i in 0..train.get_rows() {}
}
