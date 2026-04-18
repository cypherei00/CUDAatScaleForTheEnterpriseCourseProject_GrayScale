# CUDA Batch Image Grayscale Processor

## Overview

This project implements a GPU-accelerated batch image processing system using CUDA and NVIDIA Performance Primitives (NPP). The program processes a large number of input images and converts them into grayscale format efficiently using GPU computation.

The goal of this project is to demonstrate large-scale data processing using GPU acceleration instead of CPU-only approaches.

---

## Features

* GPU-based image processing using CUDA + NPP
* Batch processing of multiple images in a single run
* Command Line Interface (CLI) support
* Logs processed files into `log.txt`
* Uses OpenCV for image input/output

---

## Project Structure

```
.
├── bin/                # compiled executable
├── data/
│   ├── input/          # input images (100+ images)
│   └── output/         # output images + log.txt
├── lib/                # reserved (unused)
├── src/                # source code
│   ├── main.cpp
│   ├── image_io.cpp
│   ├── image_io.h
├── Makefile
├── run.sh
├── README.md
```

---

## Requirements

* CUDA Toolkit
* OpenCV
* Linux environment (or WSL)

### Install OpenCV (Linux)

```bash
sudo apt update
sudo apt install libopencv-dev
```

---

## Build Instructions

```bash
make
```

This will generate the executable:

```
bin/process_images
```

---

## Run Instructions

```bash
./run.sh
```

OR using CLI directly:

```bash
./bin/process_images data/input data/output
```

---

## Input Data

* Place images in:

```
data/input/
```

* The program is designed to process **100+ images** in one execution.

---

## Output

* Grayscale images are saved in:

```
data/output/
```

* Log file:

```
data/output/log.txt
```

Example log:

```
img_001.jpg processed
img_002.jpg processed
...
img_100.jpg processed
```

---

## GPU Implementation Details

The project uses the NVIDIA NPP function:

```
nppiRGBToGray_8u_C3C1R
```

Processing steps:

1. Load image using OpenCV
2. Convert BGR → RGB
3. Copy image to GPU memory
4. Apply NPP grayscale conversion
5. Copy result back to CPU
6. Save output image

---

## Execution Proof

* The program processes multiple images in a single execution
* Log file provides evidence of batch processing
* Output images confirm successful GPU computation

---

## Challenges Faced

* Managing GPU memory (cudaMalloc, cudaMemcpy)
* Linking CUDA and OpenCV correctly
* Handling batch processing efficiently
* Ensuring correct color format (BGR vs RGB)

---

## Conclusion

This project demonstrates how GPU acceleration can be used to efficiently process large datasets of images. Using CUDA and NPP significantly improves performance compared to CPU-only implementations.

---

## Future Improvements

* Add more filters (blur, edge detection)
* Compare CPU vs GPU performance
* Parallel batch processing (multi-image GPU streams)

---
