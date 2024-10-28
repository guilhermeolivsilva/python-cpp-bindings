#include <vector>
#include <random>

#include <pybind11/pybind11.h>

int add(int i, int j) {
    return i + j;
}

std::vector<std::vector<int>> generateRandomMatrix(int rows, int cols) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

std::vector<std::vector<int>> tiledMatrixMultiplication(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    int tileSize
) {
    int n = A.size();
    int m = B[0].size();
    int k = A[0].size();
    std::vector<std::vector<int>> C(n, std::vector<int>(m, 0));

    for (int i = 0; i < n; i += tileSize) {
        for (int j = 0; j < m; j += tileSize) {
            for (int x = 0; x < k; x += tileSize) {
                for (int ii = i; ii < std::min(i + tileSize, n); ++ii) {
                    for (int jj = j; jj < std::min(j + tileSize, m); ++jj) {
                        for (int xx = x; xx < std::min(x + tileSize, k); ++xx) {
                            C[ii][jj] += A[ii][xx] * B[xx][jj];
                        }
                    }
                }
            }
        }
    }

    return C;
}

int multiplyRandomMatrices(int rows, int columns, int tilesize) {
    auto matrixA = generateRandomMatrix(rows, columns);
    auto matrixB = generateRandomMatrix(rows, columns);

    auto matrixC = tiledMatrixMultiplication(matrixA, matrixB, tilesize);

    return matrixC.size() * matrixC[0].size();
}

PYBIND11_MODULE(cpp_example, m) {
    m.doc() = "pybind11 example plugin";

    m.def("add", &add, "A function that adds two numbers.");
    m.def("multiplyRandomMatrices", &multiplyRandomMatrices, "A function that generates two random matrices and multiply them.");
}
