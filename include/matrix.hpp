#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <stdexcept>

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

    Matrix& operator=(const Matrix &other) {
        if (this == &other) return *this;
        T* newitems = nullptr;
        if (other.rows * other.cols != 0) {
            newitems = new T[other.rows * other.cols];
            for (size_t i = 0; i < rows * cols; ++i) {
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

    void transfer() {
        size_t new_rows = cols;
        size_t new_cols = rows;

        T *new_items = new T[rows * cols];
        size_t i = 0;

        for (size_t j = 0; j < cols; ++j) {
            for (size_t k = 0; k < rows; ++k) {
                new_items[i++] = items[k * cols + j];
            }
        }
        delete[] items;
        cols = new_cols;
        rows = new_rows;
        items = new_items;
    }


};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j) {
            os << m(i, j) << (j + 1 == m.cols ? "" : " ");
        }
        os << '\n';
    }
    return os;
}

#endif //MATRIX_H_
