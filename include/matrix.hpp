#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <stdexcept>




template<typename T>
class ColIterator {

};

template<typename T>
class Matrix {
public:
    size_t rows;
    size_t cols;
    T *items;

    Matrix() : rows(0), cols(0), items(nullptr) {}

    Matrix(size_t r, size_t c) : rows(r), cols(c) {
        items = new T[rows * cols]();
    }

    Matrix(size_t r, size_t c, std::initializer_list<T> init)
                : rows(r), cols(c), items(new T[r * c]) {
        if (init.size() != r * c) {
            delete[] items;
            items = nullptr;
            throw std::invalid_argument("initializer_list size does not match matrix dimensions");
        }
        size_t i = 0;
        for (const auto& v : init) {
            items[i++] = v;
        }
    }

    Matrix(std::initializer_list<std::initializer_list<T>> init)
           : rows(init.size()), cols(0), items(nullptr) {
        if (rows == 0) return;

        cols = init.begin()->size();
        if (cols == 0) return;

        for (const auto& row : init) {
            if (row.size() != cols) {
                throw std::invalid_argument("All rows must have the same number of columns");
            }
        }

        items = new T[rows * cols];
        size_t idx = 0;
        for (const auto& row : init) {
            for (const auto& v : row) {
                items[idx++] = v;
            }
        }
    }

    Matrix(const Matrix &other)
        : rows(other.rows), cols(other.cols), items(nullptr) {
        if (rows * cols == 0) return;
        items = new T[rows * cols];
        for (size_t i = 0; i < rows * cols; ++i) {
            items[i] = other.items[i];
        }
    }

    Matrix(Matrix &&other) noexcept
        : rows(other.rows), cols(other.cols), items(other.items) {
            other.rows = 0;
            other.cols = 0;
            other.items = nullptr;
        }


    ~Matrix() {
        delete[] items;
        items = nullptr;
    }

    class RowIterator {
    public:
        size_t current;
        Matrix& mat;

        RowIterator(Matrix &_mat, size_t val) : mat(_mat), current(val) {}

        Matrix operator*() {
            Matrix result(1, mat.cols);
            for (size_t i = 0; i < mat.cols; ++i) {
                result(1, i + 1) = mat(current + 1, i + 1);
            }
            return result;
        }

        RowIterator& operator++() {
            ++current;
            return *this;
        }

        bool operator!=(const RowIterator& other) {
            return current != other.current;
        }
    };


    T& operator()(size_t r, size_t c) {
        if (r >= rows || c >= cols) throw std::out_of_range("Matrix index out of range");
        return items[r * cols + c];
    }

    const T& operator()(size_t r, size_t c) const {
        if (r >= rows || c >= cols) throw std::out_of_range("Matrix index out of range");
        return items[r * cols + c];
    }

    Matrix operator+(const Matrix &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw std::invalid_argument("Matrix +: dimension mismatch");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows * cols; ++i) result.items[i] = items[i] + rhs.items[i];
        return result;
    }

    Matrix& operator+=(const Matrix &rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw std::invalid_argument("Matrix +=: dimension mismatch");
        }
        for (size_t i = 0; i < rows * cols; ++i) items[i] += rhs.items[i];
        return *this;
    }

    Matrix operator-(const Matrix &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw std::invalid_argument("Matrix -: dimension mismatch");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows * cols; ++i) result.items[i] = items[i] - rhs.items[i];
        return result;
    }

    Matrix& operator-=(const Matrix &rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw std::invalid_argument("Matrix -=: dimension mismatch");
        }
        for (size_t i = 0; i < rows * cols; ++i) items[i] -= rhs.items[i];
        return *this;
    }

    Matrix operator*(const Matrix& rhs) const {
        if (cols != rhs.rows) {
            throw std::invalid_argument("Matrix *: dimension mismatch");
        }
        Matrix result(rows, rhs.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < rhs.cols; ++j) {
                T sum = T{};
                for (size_t k = 0; k < cols; ++k) {
                    sum += (*this)(i, k) * rhs(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    Matrix operator*(T other) const {
        Matrix result = *this;

        for (size_t i = 0; i < result.cols * result.rows; ++i) {
            result.items[i] *= other;
        }

        return result;
    }

    Matrix operator*=(T other) const {
        for (size_t i = 0; i < cols * rows; ++i) {
            items[i] *= other;
        }
        return *this;
    }

    Matrix& operator=(const Matrix &other) {
        if (this == &other) return *this;
        T* newitems = nullptr;
        if (other.rows * other.cols != 0) {
            newitems = new T[other.rows * other.cols];
            for (size_t i = 0; i < other.rows * other.cols; ++i) {
                newitems[i] = other.items[i];
            }
        }
        delete[] items;
        items = newitems;
        rows = other.rows;
        cols = other.cols;
        return *this;

    }

    Matrix& operator=(Matrix &&other) noexcept {
        if (this == &other) return *this;

        delete[] items;
        rows = other.rows;
        cols = other.cols;
        items = other.items;
        other.rows = 0;
        other.cols = 0;
        other.items = nullptr;
        return *this;

    }

    const Matrix& transpose() const {
        size_t new_rows = cols;
        size_t new_cols = rows;


        T *new_items = new T[rows * cols];
        size_t i = 0;

        for (size_t j = 0; j < cols; ++j) {
            for (size_t k = 0; k < rows; ++k) {
                new_items[i++] = items[k * cols + j];
            }
        }
        Matrix result(new_rows, new_cols, new_items);
    }

    Matrix take_block(size_t s_row, size_t s_col, size_t e_row, size_t e_col) {

        Matrix result(e_row - s_row + 1, (e_col - s_col + 1));

        T *new_items = new T[(e_row - s_row + 1) * (e_col - s_col + 1)];
        delete[] result.items;
        result.items = new_items;

        for (size_t i = 0; i < e_row - s_row + 1; ++i) {
            for (size_t j = 0; j < e_col - s_col + 1; ++j) {
                result(i, j) = (*this)(s_row + i - 1, s_col + j - 1);
            }
        }

        return result;

    }




};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    os << "[\n";
    for (size_t i = 0; i < m.rows; ++i) {
        os << "    ";
        for (size_t j = 0; j < m.cols; ++j) {
            os << m(i, j) << (j + 1 == m.cols ? "" : " ");
        }
        os << '\n';
    }
    os << "]\n";
    return os;
}

#endif //MATRIX_H_
