1. A python code, which runs on an Ubuntu 20.04 machine and generates output of the convolution. 
For Python code we expect you to deliver a single script, requirement.txt for prerequisites, input test vector and corresponding golden output. All the steps are expected to be clearly documented

Python implementation :


import numpy as np

def convolve(image, kernel):
    """
    Performs convolution operation between an image and a kernel.

    Args:
    image: 2D numpy array representing the input image.
    kernel: 2D numpy array representing the convolution kernel.

    Returns:
    result: 2D numpy array representing the convolved image.
    """
    image_height, image_width = image.shape
    kernel_height, kernel_width = kernel.shape
    result_height = image_height - kernel_height + 1
    result_width = image_width - kernel_width + 1
    result = np.zeros((result_height, result_width))

    for i in range(result_height):
        for j in range(result_width):
            result[i, j] = np.sum(image[i:i+kernel_height, j:j+kernel_width] * kernel)

    return result
  

# Example usage:
if __name__ == "__main__":
    image = np.array([[1, 2, 1, 2],
                      [2, 1, 2, 1],
                      [1, 2, 1, 2],
                      [2, 1, 2, 1]])

    kernel = np.array([[1, 0],
                       [0, 1]])

    result = convolve(image, kernel)
    print("Result of convolution:")
    print(result)




