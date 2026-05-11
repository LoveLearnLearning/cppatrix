#include "clustering.hpp"
#include "matrix.hpp"

int main() {
    mat::Matrix<double> mat = {
        {1, 2}
    };
    clus::kmeans(mat, 1);

}
