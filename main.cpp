#include "functions.hpp"
#include "matrix.hpp"
int main() {
    Matrix<double> train = {
        {0, 0, 0},
        {0, 1, 0},
        {1, 0, 0},
        {1, 1, 1},
    };

    Matrix<double> w(1, 2);
    func::randmat(w, 0, 1);







}
