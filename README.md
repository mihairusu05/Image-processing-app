# Image Processing Application

## Overview

This project implements a basic image processing application, designed to perform a variety of operations on grayscale images. The core tasks involve manipulating pixel values using techniques such as brightness and contrast adjustments, gamma correction, and image convolution. The application is structured around object-oriented principles, utilizing classes, inheritance, namespaces, and file I/O operations.

### Key Features
- **Image Class**: Represents a grayscale image using a 2D array of pixels, with values ranging from 0 (black) to 255 (white).
- **Image Processing Operations**: Includes operations like brightness/contrast adjustment, gamma correction, and image convolution.
- **Drawing Module**: Provides functions to draw basic shapes (circle, line, rectangle) over an image.

## Components

### Image Class
The `Image` class serves as the foundation of this application. It supports:
- Basic image operations: load, save, and manipulate pixel data.
- Arithmetic operations (addition, subtraction) on images and scalars.
- Region of Interest (ROI) extraction to work on subregions of an image.
- Memory management with deep copy mechanisms.

### Image Processing Operations
Operations are implemented through a base class `ImageProcessing`, with the following subclasses:
1. **Brightness and Contrast Adjustment**: Alters brightness and contrast using parameters \( \alpha \) (gain) and \( \beta \) (bias).
2. **Gamma Correction**: Affects image brightness based on a gamma factor \( \gamma \).
3. **Image Convolution**: Applies convolutional kernels (e.g., mean blur, Sobel filters) to extract features or blur an image.

### Drawing Module
The drawing module enables adding geometric shapes to an image:
- **Circle**: Draw a circle with specified center, radius, and color.
- **Line**: Draw a line between two points with a specific color.
- **Rectangle**: Draw a rectangle with a specified region and color.

## Requirements
- Consistent coding style throughout the project.
- Provide unit tests for all implemented functions with at least 80% code coverage.
- Prove the absence of memory leaks.
- Use Doxygen format for documentation, and generate HTML docs.
- Handle pixel values appropriately within the range [0, 255], applying clipping when necessary.

## Extra Credit Challenge
- Extend the application to work with color images, using the PPM format for color images.

## References
- **Image Convolution**: Detailed explanation of convolution operations can be found in these resources:
  - [Convolution for Image Processing](https://blog.francium.tech/machine-learning-convolution-for-image-processing-42623c8dbec0)
  - [Wikipedia: Convolution](https://en.wikipedia.org/wiki/Kernel_(image_processing))

- **Gamma Correction**: Further reading about gamma correction:
  - [Cambridge in Colour - Gamma Correction](https://www.cambridgeincolour.com/tutorials/gamma-correction.htm)
  - [Wikipedia: Gamma Correction](https://en.wikipedia.org/wiki/Gamma_correction)

## Setup and Usage
1. Clone the repository.
2. Build the project.
3. Run the application and apply image processing tasks using the provided operations.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
