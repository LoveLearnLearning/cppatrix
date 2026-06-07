use std::{
    fmt,
    ops::{Add, AddAssign, Div, Mul, MulAssign, Sub, SubAssign},
};

#[derive(Clone, Debug, PartialEq)]
pub struct Matrix<T> {
    rows: usize,
    cols: usize,
    data: Vec<T>,
}

impl<T: Default + Clone> Matrix<T> {
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
    fn add(self, rhs: Self) -> Self::Output {
        assert_eq!(self.rows, rhs.rows);
        assert_eq!(self.cols, rhs.cols);
        let mut result = self;
        for i in 0..result.data.len() {
            result.data[i] += rhs.data[i].clone();
        }
        result
    }
}

impl<T: Clone + Sub<Output = T> + SubAssign> Sub for Matrix<T> {
    type Output = Matrix<T>;
    fn sub(self, rhs: Self) -> Self::Output {
        assert_eq!(self.rows, rhs.rows);
        assert_eq!(self.cols, rhs.cols);
        let mut result = self;
        for i in 0..result.data.len() {
            result.data[i] -= rhs.data[i].clone();
        }
        result
    }
}

impl<T: Clone + Mul<Output = T>> Mul for Matrix<T> {
    type Output = Matrix<T>;
    fn mul(self, rhs: Self) -> Self::Output {
        assert_eq!(self.cols, rhs.rows);
    }
}

impl<T: fmt::Display> fmt::Display for Matrix<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "[\n")?;
        for i in 0..self.rows {
            write!(f, "    ")?;
            for j in 0..self.cols {
                write!(f, "{}", self.data[i * self.cols + j])?;
                if j + 1 < self.cols {
                    write!(f, " ")?;
                }
            }
            write!(f, "\n")?;
        }
        write!(f, "]")
    }
}

fn main() {
    let m1 = Matrix::<i32>::new(1, 3);
    println!("{}", m1);
    let mut m2 = Matrix::from_vec(1, 3, vec![1, 2, 3]);
    m2 = m2 + m1.clone();
    println!("{}", m1);
    println!("{}", m2);
}
