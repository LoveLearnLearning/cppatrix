use std::{
    fmt::{self},
    ops::{Add, AddAssign, Div, DivAssign, Index, IndexMut, Mul, MulAssign, Sub, SubAssign},
};

#[derive(Clone, Debug, PartialEq)]
pub struct Matrix<T> {
    rows: usize,
    cols: usize,
    data: Vec<T>,
}

impl<T: Default + Clone> Matrix<T> {
    pub fn new(r: usize, c: usize) -> Self {
        Self {
            rows: (r),
            cols: (c),
            data: (vec![T::default(); r * c]),
        }
    }

    pub fn from_vec(r: usize, c: usize, _data: Vec<T>) -> Self {
        assert_eq!(r * c, _data.len());
        Self {
            rows: (r),
            cols: (c),
            data: (_data),
        }
    }

    pub fn row_iter(&self) -> RowIter<'_, T> {
        RowIter {
            matrix: (self),
            current: (0),
        }
    }

    pub fn col_iter(&self) -> ColIter<'_, T> {
        ColIter {
            matrix: (self),
            current: (0),
        }
    }

    pub fn row(&self, i: usize) -> &[T] {
        &self.data[i * self.cols..(i + 1) * self.cols]
    }

    pub fn get_rows(&self) -> usize {
        self.rows
    }

    pub fn get_cols(&self) -> usize {
        self.cols
    }
}

impl<T: Clone> Index<(usize, usize)> for Matrix<T> {
    type Output = T;
    fn index(&self, (r, c): (usize, usize)) -> &Self::Output {
        &self.data[r * self.cols + c]
    }
}

impl<T: Clone> IndexMut<(usize, usize)> for Matrix<T> {
    fn index_mut(&mut self, (r, c): (usize, usize)) -> &mut Self::Output {
        &mut self.data[r * self.cols + c]
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

pub struct RowIter<'a, T> {
    matrix: &'a Matrix<T>,
    current: usize,
}

impl<'a, T> Iterator for RowIter<'a, T> {
    type Item = &'a [T];
    fn next(&mut self) -> Option<Self::Item> {
        if self.current < self.matrix.rows {
            let start = self.current * self.matrix.cols;
            self.current += 1;
            Some(&self.matrix.data[start..start + self.matrix.cols])
        } else {
            None
        }
    }
}

pub struct ColIter<'a, T> {
    matrix: &'a Matrix<T>,
    current: usize,
}

impl<'a, T> Iterator for ColIter<'a, T> {
    type Item = Vec<&'a T>;
    fn next(&mut self) -> Option<Self::Item> {
        if self.current < self.matrix.cols {
            let col = (0..self.matrix.rows)
                .map(|r| &self.matrix.data[r * self.matrix.cols + self.current])
                .collect();
            self.current += 1;
            Some(col)
        } else {
            None
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
