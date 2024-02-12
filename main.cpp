#include <iostream>
#include <vector>

std::vector<std::vector<int>> convolve(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& kernel) {
    int image_height = image.size();
    int image_width = image[0].size();
    int kernel_height = kernel.size();
    int kernel_width = kernel[0].size();
    int result_height = image_height - kernel_height + 1;
    int result_width = image_width - kernel_width + 1;
    std::vector<std::vector<int>> result(result_height, std::vector<int>(result_width, 0));

    for (int i = 0; i < result_height; ++i) {
        for (int j = 0; j < result_width; ++j) {
            for (int ki = 0; ki < kernel_height; ++ki) {
                for (int kj = 0; kj < kernel_width; ++kj) {
                    result[i][j] += image[i + ki][j + kj] * kernel[ki][kj];
                }
            }
        }
    }

    return result;
}

int main() {
    std::vector<std::vector<int>> image = {{1, 2, 1, 2},
                                            {2, 1, 2, 1},
                                            {1, 2, 1, 2},
                                            {2, 1, 2, 1}};

    std::vector<std::vector<int>> kernel = {{1, 0},
                                             {0, 1}};

    auto result = convolve(image, kernel);

    std::cout << "Result of convolution:" << std::endl;
    for (const auto& row : result) {
        for (int pixel : row) {
            std::cout << pixel << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
