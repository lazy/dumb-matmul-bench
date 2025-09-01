#!/usr/bin/env python3

import sys
import numpy as np
import time

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <matrix_size>", file=sys.stderr)
        sys.exit(1)
    
    try:
        n = int(sys.argv[1])
        if n <= 0:
            print("Matrix size must be positive", file=sys.stderr)
            sys.exit(1)
    except ValueError:
        print("Matrix size must be an integer", file=sys.stderr)
        sys.exit(1)

    try:
        cfg = np.show_config('dicts')['Build Dependencies']['blas']
        blas_library = cfg['name'] + ' ' + cfg['version']
    except:
        blas_library = 'unknown'
    print(f'Blas implementation: {blas_library}')

    # Generate random matrices
    print(f"Generating {n}x{n} matrices...", file=sys.stderr)
    np.random.seed(42)  # For reproducible results
    A = np.random.uniform(-1.0, 1.0, (n, n)).astype(np.float64, order='F')
    B = np.random.uniform(-1.0, 1.0, (n, n)).astype(np.float64, order='F')
    C = np.empty((n, n), dtype=np.float64, order='F')

    # Measure time for matrix multiplication
    print(f"Multiplying {n}x{n} matrices...", file=sys.stderr)
    start_time = time.perf_counter()
    np.matmul(A, B, out=C)
    end_time = time.perf_counter()

    # Calculate timing and performance
    elapsed_time = end_time - start_time
    flops = 2.0 * n * n * n
    gflops = flops / (elapsed_time * 1e9)

    # Output in same format as C++ program
    print(f"Matrix size: {n}x{n}")
    print(f"Time taken: {elapsed_time:.6f} seconds")
    print(f"Performance: {gflops:.2f} GFLOPS")

if __name__ == "__main__":
    main()
