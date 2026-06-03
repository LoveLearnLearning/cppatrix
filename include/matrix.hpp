#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <initializer_list>
#include <ostream>
#include <stdexcept>

namespace mat {

enum class Axis {
    ROW,
    COL,
};

template <typename T> class Matrix {
  public:
    size_t rows;
    size_t cols;
    T *items;

    Matrix() : rows(0), cols(0), items(nullptr) {}

    Matrix(size_t r, size_t c) : rows(r), cols(c) { items = new T[rows * cols](); }

    Matrix(size_t r, size_t c, std::initializer_list<T> init)
        : rows(r), cols(c), items(new T[r * c]) {
        if (init.size() != r * c) {
            delete[] items;
            items = nullptr;
            throw std::invalid_argument("initializer_list size does not match matrix dimensions");
        }
        size_t i = 0;
        for (const auto &v : init) {
            items[i++] = v;
        }
    }

    Matrix(std::initializer_list<std::initializer_list<T>> init)
        : rows(init.size()), cols(0), items(nullptr) {
        if (rows == 0)
            return;

        cols = init.begin()->size();
        if (cols == 0)
            return;

        for (const auto &row : init) {
            if (row.size() != cols) {
                throw std::invalid_argument("All rows must have the same number of columns");
            }
        }

        items = new T[rows * cols];
        size_t idx = 0;
        for (const auto &row : init) {
            for (const auto &v : row) {
                items[idx++] = v;
            }
        }
    }

    Matrix(const Matrix &other) : rows(other.rows), cols(other.cols), items(nullptr) {
        if (rows * cols == 0)
            return;
        items = new T[rows * cols];
        for (size_t i = 0; i < rows * cols; ++i) {
            items[i] = other.items[i];
        }
    }

    Matrix(Matrix &&other) noexcept : rows(other.rows), cols(other.cols), items(other.items) {
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
        Matrix *mat;

        RowIterator(Matrix *_mat, size_t val) : mat(_mat), current(val) {}

        Matrix operator*() {
            Matrix result(1, mat->cols);
            for (size_t i = 0; i < mat->cols; ++i) {
                result(0, i) = (*mat)(current, i);
            }
            return result;
        }

        RowIterator &operator++() {
            ++current;
            return *this;
        }

        bool operator!=(const RowIterator &other) { return current != other.current; }
    };

    class ColIterator {
      private:
        size_t current;
        Matrix *mat;

      public:
        ColIterator(Matrix *_mat, size_t val) : mat(_mat), current(val) {}

        Matrix operator*() {
            Matrix result(mat->rows, 1);
            for (size_t i = 0; i < mat->rows; ++i) {
                result(i, 0) = (*mat)(i, current);
            }
            return result;
        }

        ColIterator &operator++() {
            ++current;
            return *this;
        }

        bool operator!=(const ColIterator &other) { return current != other.current; }
    };

    class ColView {
      private:
        Matrix *mat;

      public:
        ColView(Matrix *_mat) : mat(_mat) {}

        ColIterator begin() { return ColIterator(this->mat, 0); }
        ColIterator end() { return ColIterator(this->mat, this->mat->cols); }

        class ColProxy {
            T *data;
            size_t rows;
            size_t stride;

          public:
            ColProxy(T *d, size_t r, size_t s) : data(d), rows(r), stride(s) {}

            T &operator[](size_t row) { return data[row * stride]; }
            const T &operator[](size_t row) const { return data[row * stride]; }

            operator Matrix() const {
                Matrix result(rows, 1);
                for (size_t i = 0; i < rows; ++i)
                    result.items[i] = data[i * stride];
                return result;
            }

            ColProxy &operator=(const Matrix &other) {
                if (other.cols != 1 || other.rows != rows)
                    throw std::invalid_argument("ColProxy =: dimention mismatch");
                for (size_t i = 0; i < rows; ++i)
                    data[i * stride] = other.items[i];
                return *this;
            }

            ColProxy &operator=(const ColProxy &other) {
                if (other.rows != rows)
                    throw std::invalid_argument("ColProxy =: dimention mismatch");
                for (size_t i = 0; i < rows; ++i)
                    data[i * stride] = other.data[i * other.stride];
                return *this;
            }
        };

        ColProxy operator[](size_t col) {
            return ColProxy(this->mat->items + col, this->mat->rows, this->mat->cols);
        }
    };

    ColView col_view() { return ColView(this); }

    class RowView {
      private:
        Matrix *mat;

      public:
        RowView(Matrix *_mat) : mat(_mat) {}

        RowIterator begin() { return RowIterator(this->mat, 0); }
        RowIterator end() { return RowIterator(this->mat, this->mat->rows); }

        class RowProxy {
            T *data;
            size_t cols;

          public:
            RowProxy(T *d, size_t c) : data(d), cols(c) {}

            T &operator[](size_t col) { return data[col]; }
            const T &operator[](size_t col) const { return data[col]; }

            operator Matrix() const {
                Matrix result(1, cols);
                for (size_t i = 0; i < cols; ++i)
                    result.items[i] = data[i];
                return result;
            }

            RowProxy &operator=(const Matrix &other) {
                if (other.rows != 1 || other.cols != cols)
                    throw std::invalid_argument("RowProxy =: dimension mismatch");
                for (size_t i = 0; i < cols; ++i)
                    data[i] = other.items[i];
                return *this;
            }

            RowProxy &operator=(const RowProxy &other) {
                if (other.cols != cols)
                    throw std::invalid_argument("RowProxy =: dimension mismatch");
                for (size_t i = 0; i < cols; ++i)
                    data[i] = other.data[i];
                return *this;
            }
        };

        RowProxy operator[](size_t row) {
            return RowProxy(this->mat->items + row * this->mat->cols, this->mat->cols);
        }
    };

    RowView row_view() { return RowView(this); }

    T &operator()(size_t r, size_t c) {
        if (r >= rows || c >= cols)
            throw std::out_of_range("Matrix index out of range");
        return items[r * cols + c];
    }

    const T &operator()(size_t r, size_t c) const {
        if (r >= rows || c >= cols)
            throw std::out_of_range("Matrix index out of range");
        return items[r * cols + c];
    }

    Matrix operator+(const Matrix &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw std::invalid_argument("Matrix +: dimension mismatch");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows * cols; ++i)
            result.items[i] = items[i] + rhs.items[i];
        return result;
    }

    Matrix &operator+=(const Matrix &rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw std::invalid_argument("Matrix +=: dimension mismatch");
        }
        for (size_t i = 0; i < rows * cols; ++i)
            items[i] += rhs.items[i];
        return *this;
    }

    Matrix operator-(const Matrix &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw std::invalid_argument("Matrix -: dimension mismatch");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows * cols; ++i)
            result.items[i] = items[i] - rhs.items[i];
        return result;
    }

    Matrix &operator-=(const Matrix &rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw std::invalid_argument("Matrix -=: dimension mismatch");
        }
        for (size_t i = 0; i < rows * cols; ++i)
            items[i] -= rhs.items[i];
        return *this;
    }

    Matrix operator*(const Matrix &rhs) const {
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

    Matrix &operator*=(T other) {
        for (size_t i = 0; i < cols * rows; ++i) {
            items[i] *= other;
        }
        return *this;
    }

    Matrix operator/(T other) const {
        Matrix result = *this;

        for (size_t i = 0; i < result.cols * result.rows; ++i) {
            result.items[i] /= other;
        }

        return result;
    }

    Matrix &operator/=(T other) {
        for (size_t i = 0; i < cols * rows; ++i) {
            items[i] /= other;
        }
        return *this;
    }

    Matrix &operator=(const Matrix &other) {
        if (this == &other)
            return *this;
        T *newitems = nullptr;
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

    Matrix &operator=(Matrix &&other) noexcept {
        if (this == &other)
            return *this;

        delete[] items;
        rows = other.rows;
        cols = other.cols;
        items = other.items;
        other.rows = 0;
        other.cols = 0;
        other.items = nullptr;
        return *this;
    }

    bool operator==(const Matrix &other) const noexcept {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }
        for (size_t i = 0; i < rows * cols; ++i) {
            if (items[i] != other.items[i])
                return false;
        }
        return true;
    }

    Matrix transpose() const {
        size_t new_rows = cols;
        size_t new_cols = rows;

        Matrix result(new_rows, new_cols);

        T *new_items = new T[rows * cols];
        size_t i = 0;

        for (size_t j = 0; j < cols; ++j) {
            for (size_t k = 0; k < rows; ++k) {
                new_items[i++] = items[k * cols + j];
            }
        }
        T *temp = result.items;
        result.items = new_items;
        delete[] temp;
        return result;
    }

    Matrix take_block(size_t s_row, size_t s_col, size_t e_row, size_t e_col) {

        if (e_row >= rows || e_col >= cols || s_row > e_row || s_col > e_col)
            throw std::out_of_range("take_block: index out of range");

        Matrix result(e_row - s_row + 1, (e_col - s_col + 1));

        T *new_items = new T[(e_row - s_row + 1) * (e_col - s_col + 1)];
        T *temp = result.items;
        result.items = new_items;
        delete[] temp;

        for (size_t i = 0; i < e_row - s_row + 1; ++i) {
            for (size_t j = 0; j < e_col - s_col + 1; ++j) {
                result(i, j) = (*this)(s_row + i, s_col + j);
            }
        }

        return result;
    }

    Matrix hadamard(const Matrix &rhs) const {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw std::out_of_range("hadamard: dimension mismatch!");
        }

        Matrix result(rows, cols);

        for (size_t i = 0; i < rows * cols; ++i) {
            result.items[i] = items[i] * rhs.items[i];
        }
        return result;
    }

    Matrix sum(Axis axis) const {
        if (axis == Axis::ROW) {
            Matrix result(rows, 1);
            for (size_t i = 0; i < rows; ++i) {
                T sum = 0;
                for (size_t j = 0; j < cols; ++j) {
                    sum += items[i * cols + j];
                }
                result.items[i] = sum;
            }
            return result;
        } else if (axis == Axis::COL) {
            Matrix result(1, cols);
            for (size_t i = 0; i < cols; ++i) {
                T sum = 0;
                for (size_t j = 0; j < rows; ++j) {
                    sum += items[j * cols + i];
                }
                result.items[i] = sum;
            }
            return result;
        } else {
            throw std::runtime_error("UNKNOWN Axis type, example: ROW, COL");
        }
    }

    Matrix mean(Axis axis) const {
        if (axis == Axis::ROW) {
            Matrix result(rows, 1);
            for (size_t i = 0; i < rows; ++i) {
                T sum = 0;
                for (size_t j = 0; j < cols; ++j) {
                    sum += items[i * cols + j];
                }
                result.items[i] = sum / cols;
            }
            return result;
        } else if (axis == Axis::COL) {
            Matrix result(1, cols);
            for (size_t i = 0; i < cols; ++i) {
                T sum = 0;
                for (size_t j = 0; j < rows; ++j) {
                    sum += items[j * cols + i];
                }
                result.items[i] = sum / rows;
            }
            return result;
        } else {
            throw std::runtime_error("UNKNOWN Axis type, example: ROW, COL");
        }
    }

    static Matrix zeros(size_t r, size_t c) { return Matrix(r, c); }

    static Matrix ones(size_t r, size_t c) {
        Matrix result(r, c);
        for (size_t i = 0; i < r * c; ++i) {
            result.items[i] = 1;
        }
        return result;
    }

    static Matrix eye(size_t n) {
        Matrix result(n, n);
        for (size_t i = 0; i < n; ++i) {
            result(i, i) = 1;
        }
        return result;
    }
};

template <typename T> std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) {
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
} // namespace mat

#endif // MATRIX_HPP_
