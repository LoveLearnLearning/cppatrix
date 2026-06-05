pub struct Matrix<T> {
    rows: usize,
    cols: usize,
    data: Vec<T>,
}

impl<T: Default + Clone> Matrix<T> {
    fn new(r: usize, c: usize) -> Self {
        Self { rows: (r), cols: (c), data: (vec![T::default(); r * c]) }
    }
}

fn main() {

    let m = Matrix::<f32>::new(1, 3);

}
