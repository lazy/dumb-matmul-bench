CXX = g++
CXXFLAGS = -O3 -m64 -march=native -std=c++17

# This will automatically use the right flags for multi-threaded MKL
MKL_FLAGS = $(shell pkg-config --cflags --libs mkl-sdl 2>/dev/null || \
             pkg-config --cflags --libs mkl 2>/dev/null || \
             echo "-I/opt/intel/oneapi/mkl/latest/include -L/opt/intel/oneapi/mkl/latest/lib/intel64 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm -ldl")

TARGET = matrix_mult
SOURCE = matrix_mult.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) $(MKL_FLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
