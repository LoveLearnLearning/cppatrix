use std::{
    ops::{Add, AddAssign, Div, Mul, Sub},
    process::Output,
    result,
};

pub struct Matrix<T> {
    rows: usize,
    cols: usize,
    data: Vec<T>,
}

impl<T> Matrix<T>
where
    T: Default
        + Clone
        + Add<Output = T>
        + Sub<Output = T>
        + Mul<Output = T>
        + Div<Output = T>
        + AddAssign,
{
    fn new(r: usize, c: usize) -> Self {
        Self {
            rows: (r),
            cols: (c),
            data: (vec![T::default(); r * c]),
        }
    }

    fn from_vec(r: usize, c: usize, _data: Vec<T>) -> Self {
        assert_eq!(r * c, _data.len());
        Self {
            rows: (r),
            cols: (c),
            data: (_data),
        }
    }
}

impl<T: Clone + Add<Output = T> + AddAssign> Add for Matrix<T> {
    type Output = Matrix<T>;
    fn add(self, rhs: Self) -> Self {
        assert_eq!(self.rows, rhs.rows);
        assert_eq!(self.cols, rhs.cols);
        let mut result = self;
        for i in 0..result.data.len() {
            result.data[i] += rhs.data[i].clone();
        }
        result
    }
}

fn main() {
    let m1 = Matrix::<f32>::new(1, 3);
    let mut m2 = Matrix::from_vec(1, 2, vec![1, 2]);

    println!("{:?}", m1.data);
    m2.data[1] = 3;
}
