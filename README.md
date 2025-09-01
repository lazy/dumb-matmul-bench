# Dumb matmul bench

The only purpose is showing that matmul in Anaconda is done using
Intel MKL library and performance is exactly the same between C++ and
Python code calling into it. All code besides `bench.sh` is written by
`qwen3-coder-480b`.

On my machine results are these:

```
> ./bench.sh
=== Building
g++ -O3 -m64 -march=native -std=c++17 matrix_mult.cpp -I/opt/intel/oneapi/mkl/latest/include -L/opt/intel/oneapi/mkl/latest/lib/intel64 -lmkl_rt -lpthread -lm -ldl  -o matrix_mult
=== C++
MKL version: 2023.0
Matrix size: 16384x16384
Time taken: 6.15184 seconds
Performance: 1429.83 GFLOPS
=== Python
Blas implementation: mkl-sdl
Generating 16384x16384 matrices...
Multiplying 16384x16384 matrices...
Matrix size: 16384x16384
Time taken: 6.349443 seconds
Performance: 1385.33 GFLOPS
```

To build install MKL using your system package manager. I used python
from recent Anaconda download.
