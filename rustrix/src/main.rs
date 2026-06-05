pub struct Matrix<T> {
    rows: usize,
    cols: usize,
    data: Vec<T>,
}

impl<T: Default + Clone> Matrix<T> {
    fn new(r: usize, c: usize) -> Self {
        Self { rows: (r), cols: (c), data: (vec![T::default(); r * c]) }
    }

    fn from_vec(r: usize, c: usize, _data: Vec<T>) -> Self {
        assert_eq!(r * c, _data.len());
        Self { rows: (r), cols: (c), data: (_data) }
    }
}

fn main() {

    let m1 = Matrix::<f32>::new(1, 3);
    let mut m2 = Matrix::from_vec(
        1,
        2,
        vec![1, 2],
    );

}
