#include <iostream>
#include <random>
#include <chrono>
#include <mkl.h>
#include <cstdlib>

void initialize_matrix(double* matrix, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    for (int i = 0; i < size * size; ++i) {
        matrix[i] = dis(gen);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <matrix_size>" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Matrix size must be positive" << std::endl;
        return 1;
    }

    MKLVersion version;
    mkl_get_version(&version);

    std::cout << "=== Intel MKL Version Information ===" << std::endl;
    std::cout << "MKL version: " << version.MajorVersion << "." << version.MinorVersion << std::endl;

    // Allocate memory for matrices
    double* A = new double[n * n];
    double* B = new double[n * n];
    double* C = new double[n * n];

    // Initialize matrices with random values
    initialize_matrix(A, n);
    initialize_matrix(B, n);

    // Set alpha and beta for GEMM operation (C = alpha*A*B + beta*C)
    double alpha = 1.0;
    double beta = 0.0;

    // Measure time for matrix multiplication
    auto start = std::chrono::high_resolution_clock::now();

    // Perform matrix multiplication: C = A * B
    // Note: MKL uses column-major order, so we compute B^T * A^T = (A * B)^T
    // This gives us the correct result in column-major format
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
                n, n, n, alpha, A, n, B, n, beta, C, n);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    double time_seconds = duration.count() / 1000000.0;
    double gflops = (2.0 * n * n * n) / (time_seconds * 1e9);

    std::cout << "Matrix size: " << n << "x" << n << std::endl;
    std::cout << "Time taken: " << time_seconds << " seconds" << std::endl;
    std::cout << "Performance: " << gflops << " GFLOPS" << std::endl;

    // Clean up
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
