use std::ops::{Add, AddAssign, Mul};

use crate::matrix::Matrix;

fn forward<T: Default + Clone + Add<Output = T> + AddAssign + Mul<Output = T>>(
    params: &Matrix<T>,
    weight: &Matrix<T>,
    bais: &Matrix<T>,
) -> Matrix<T> {
    weight.clone() * params.clone() + bais.clone()
}
