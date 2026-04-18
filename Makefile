CUDA_PATH ?= /usr/local/cuda

NVCC = nvcc

CXXFLAGS = -std=c++17 \
           -I/usr/include/opencv4 \
           -I$(CUDA_PATH)/include

LDFLAGS = -lopencv_core -lopencv_imgcodecs -lopencv_imgproc \
          -L$(CUDA_PATH)/lib64 -lcudart -lnppc -lnppial

SRC = src/main.cpp src/image_io.cpp
OUT = bin/process_images

all:
	mkdir -p bin
	$(NVCC) $(SRC) -o $(OUT) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf bin/*