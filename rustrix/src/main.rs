use std::{
    fmt::{self},
    ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Sub, SubAssign},
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

impl<T: Default + Clone + Mul<Output = T> + AddAssign> Mul<Matrix<T>> for Matrix<T> {
    type Output = Matrix<T>;
    fn mul(self, rhs: Self) -> Self::Output {
        assert_eq!(self.cols, rhs.rows);
        let mut result = Matrix::<T>::new(self.rows, rhs.cols);

        for i in 0..self.rows {
            for j in 0..rhs.cols {
                for k in 0..self.cols {
                    result.data[i * rhs.cols + j] +=
                        self.data[i * self.cols + k].clone() * rhs.data[k * rhs.cols + j].clone();
                }
            }
        }
        result
    }
}

impl<T: Default + Clone + Mul<Output = T> + MulAssign> Mul<T> for Matrix<T> {
    type Output = Matrix<T>;
    fn mul(self, rhs: T) -> Self::Output {
        let mut result = self.clone();
        for i in 0..result.data.len() {
            result.data[i] *= rhs.clone();
        }
        result
    }
}

impl<T: Clone + MulAssign> MulAssign<T> for Matrix<T> {
    fn mul_assign(&mut self, rhs: T) {
        for i in 0..self.data.len() {
            self.data[i] *= rhs.clone();
        }
    }
}

impl<T: Clone + Div<Output = T> + DivAssign> Div<T> for Matrix<T> {
    type Output = Matrix<T>;
    fn div(self, rhs: T) -> Self::Output {
        let mut result = self.clone();
        for i in 0..result.data.len() {
            result.data[i] /= rhs.clone();
        }
        result
    }
}

impl<T: Clone + DivAssign> DivAssign<T> for Matrix<T> {
    fn div_assign(&mut self, rhs: T) {
        for i in 0..self.data.len() {
            self.data[i] /= rhs.clone();
        }
    }
}

impl<T: Clone + AddAssign> AddAssign for Matrix<T> {
    fn add_assign(&mut self, rhs: Self) {
        assert_eq!(self.rows, rhs.rows);
        assert_eq!(self.cols, rhs.cols);
        for i in 0..self.data.len() {
            self.data[i] += rhs.data[i].clone();
        }
    }
}

impl<T: Clone + SubAssign> SubAssign for Matrix<T> {
    fn sub_assign(&mut self, rhs: Self) {
        assert_eq!(self.rows, rhs.rows);
        assert_eq!(self.cols, rhs.cols);
        for i in 0..self.data.len() {
            self.data[i] -= rhs.data[i].clone();
        }
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
    let m3 = Matrix::from_vec(3, 1, vec![3, 2, 1]);
    let m4 = m1.clone() * m3;
    println!("{}", m1);
    let mut m5 = m4 * 2;
    println!("{}", m2);
}
